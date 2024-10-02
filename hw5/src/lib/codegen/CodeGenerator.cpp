#include "codegen/CodeGenerator.hpp"
#include "visitor/AstNodeInclude.hpp"

#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cstdio>

CodeGenerator::CodeGenerator(const std::string &source_file_name,
                             const std::string &save_path,
                             const SymbolManager *const p_symbol_manager)
    : m_symbol_manager_ptr(p_symbol_manager),
      m_source_file_path(source_file_name) {
    // FIXME: assume that the source file is always xxxx.p
    const auto &real_path =
        save_path.empty() ? std::string{"."} : save_path;
        // source_file_name.empty() ? std::string{"."} : source_file_name;
    auto slash_pos = source_file_name.rfind("/");
    auto dot_pos = source_file_name.rfind(".");

    if (slash_pos != std::string::npos) {
        ++slash_pos;
    } else {
        slash_pos = 0;
    }
    auto output_file_path{
        real_path + "/" + 
        source_file_name.substr(slash_pos, dot_pos - slash_pos) + ".S"};
    m_output_file.reset(fopen(output_file_path.c_str(), "w"));
    assert(m_output_file.get() && "Failed to open output file");

    // printf("real path:%s\n",real_path.c_str());
}

static void dumpInstructions(FILE *p_out_file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(p_out_file, format, args);
    va_end(args);
}

void CodeGenerator::visit(ProgramNode &p_program) {
    // Generate RISC-V instructions for program header
    // clang-format off
    constexpr const char *const riscv_assembly_file_prologue =
        "    .file \"%s\"\n"
        "    .option nopic\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), riscv_assembly_file_prologue,
                     m_source_file_path.c_str());

    // Reconstruct the hash table for looking up the symbol entry
    // Hint: Use symbol_manager->lookup(symbol_name) to get the symbol entry.
    m_symbol_manager_ptr->reconstructHashTableFromSymbolTable(
        p_program.getSymbolTable());

    label = 1;

    auto visit_ast_node = [&](auto &ast_node) { ast_node->accept(*this); };
    global_var_flag = 1;
    for_each(p_program.getDeclNodes().begin(), p_program.getDeclNodes().end(),
             visit_ast_node);
    global_var_flag = 0;
    for_each(p_program.getFuncNodes().begin(), p_program.getFuncNodes().end(),
             visit_ast_node);

    // clang-format off
    constexpr const char *const go_main =
        ".section    .text\n"
        "    .align 2\n"
        "    .globl main\n"
        "    .type main, @function\n"
        "main:\n"
        "    addi sp, sp, -128 ### compound statement, start compound statement assembly\n"
        "    sw ra, 124(sp)\n"
        "    sw s0, 120(sp)\n"
        "    addi s0, sp, 128\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), go_main);

    offset = -12;
    const_cast<CompoundStatementNode &>(p_program.getBody()).accept(*this);
    


    constexpr const char *const main_end =
        "    lw ra, 124(sp) ### compound statement, end compound statement assembly\n"
        "    lw s0, 120(sp)\n"
        "    addi sp, sp, 128\n"
        "    jr ra\n"
        "    .size main, .-main\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), main_end);

    fclose(m_output_file.get());

    // Remove the entries in the hash table
    m_symbol_manager_ptr->removeSymbolsFromHashTable(p_program.getSymbolTable());
}

void CodeGenerator::visit(DeclNode &p_decl) {
    auto visit_ast_node = [&](auto &ast_node) { ast_node->accept(*this); };
    for_each(p_decl.getVariables().begin(), p_decl.getVariables().end(),
             visit_ast_node);
}

void CodeGenerator::visit(VariableNode &p_variable) {
    if(global_var_flag){
        if(p_variable.getConstantPtr()){
            // clang-format off
            constexpr const char *const output =
                ".section    .rodata\n"
                "    .align 2\n"
                "    .globl %s\n"
                "    .type %s, @object\n"
                "%s:\n"
                ;
            // clang-format on
            dumpInstructions(m_output_file.get(), output, p_variable.getNameCString(), p_variable.getNameCString(), p_variable.getNameCString());

            p_variable.visitChildNodes(*this);
        }
        else{
            // clang-format off
            constexpr const char *const output =
                ".comm %s, 4, 4\n"
                ;
            // clang-format on
            dumpInstructions(m_output_file.get(), output, p_variable.getNameCString());
        }
    }
    else{
        SymbolEntry *cur = m_symbol_manager_ptr->lookup(p_variable.getNameCString());
        cur->on_stack = offset;

        if(is_function){
            // marker, function argument

            // clang-format off
            constexpr const char *const output =
                "    sw a%d, %d(s0)  # save parameter %s\n"
                ;
            // clang-format on
            // clang-format off
            constexpr const char *const output_argument_more_8 =
                "    sw t%d, %d(s0)  # save parameter %s\n"
                ;
            // clang-format on

            if(parameter_num > 7) dumpInstructions(m_output_file.get(), output_argument_more_8, parameter_num-8, offset, p_variable.getNameCString());
            else dumpInstructions(m_output_file.get(), output, parameter_num, offset, p_variable.getNameCString());
            parameter_num++;
        }
        
        if(p_variable.getConstantPtr()){
            // clang-format off
            constexpr const char *const output =
                "    addi t0, s0, %d ### variable, has constant value\n"
                "    addi sp, sp, -4\n"
                "    sw t0, 0(sp)  # push %s\n"
                ;
            // clang-format on
            dumpInstructions(m_output_file.get(), output, offset, p_variable.getNameCString());

            p_variable.visitChildNodes(*this);

            // clang-format off
            constexpr const char *const output2 =
                "    lw t0, 0(sp) ### variable, give value\n"
                "    addi sp, sp, 4\n"
                "    lw t1, 0(sp)\n"
                "    addi sp, sp, 4\n"
                "    sw t0, 0(t1)\n"
                ;
            // clang-format on
            dumpInstructions(m_output_file.get(), output2);
        }

        offset -= 4;
    }
}

void CodeGenerator::visit(ConstantValueNode &p_constant_value) {
    if(global_var_flag){
        // clang-format off
        constexpr const char *const output =
            "   .word %s\n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), output, p_constant_value.getConstantValueCString());
    }
    else{
        // clang-format off
        constexpr const char *const output =
            "    li t0, %s ### constant value\n"
            "    addi sp, sp, -4\n"
            "    sw t0, 0(sp)\n"
            ;
        // clang-format on
        if(strcmp(p_constant_value.getConstantValueCString(),"true") == 0)dumpInstructions(m_output_file.get(), output,  "1");
        else if(strcmp(p_constant_value.getConstantValueCString(),"false") == 0)dumpInstructions(m_output_file.get(), output,  "0");
        else dumpInstructions(m_output_file.get(), output, p_constant_value.getConstantValueCString());
    }
}

void CodeGenerator::visit(FunctionNode &p_function) {
    // Reconstruct the hash table for looking up the symbol entry
    m_symbol_manager_ptr->reconstructHashTableFromSymbolTable(
        p_function.getSymbolTable());

    // clang-format off
    constexpr const char *const function =
        ".section    .text ### function\n"
        "    .align 2\n"
        "    .globl %s\n"
        "    .type %s, @function\n"
        "%s:\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), function, p_function.getNameCString(), p_function.getNameCString(), p_function.getNameCString());

    // clang-format off
    constexpr const char *const function_compound_statement =
        "    addi sp, sp, -128 # function compound statement\n"
        "    sw ra, 124(sp)\n"
        "    sw s0, 120(sp)\n"
        "    addi s0, sp, 128\n";
    // clang-format on
    dumpInstructions(m_output_file.get(),function_compound_statement);    

    offset = -12;
    is_function = 1;
    parameter_num = 0;
    p_function.visitChildNodes(*this);
    is_function = 0;

    constexpr const char *const function_end =
        "    lw ra, 124(sp) ### compound statement, end compound statement assembly\n"
        "    lw s0, 120(sp)\n"
        "    addi sp, sp, 128\n"
        "    jr ra\n"
        "    .size %s, .-%s\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), function_end, p_function.getNameCString(), p_function.getNameCString());

    // Remove the entries in the hash table
    m_symbol_manager_ptr->removeSymbolsFromHashTable(p_function.getSymbolTable());
}

void CodeGenerator::visit(CompoundStatementNode &p_compound_statement) {
    // Reconstruct the hash table for looking up the symbol entry
    m_symbol_manager_ptr->reconstructHashTableFromSymbolTable(
        p_compound_statement.getSymbolTable());

    if(is_function) is_function = 0;

    p_compound_statement.visitChildNodes(*this);

    // Remove the entries in the hash table
    m_symbol_manager_ptr->removeSymbolsFromHashTable(
        p_compound_statement.getSymbolTable());
}

void CodeGenerator::visit(PrintNode &p_print) {
    load_val = 1;
    p_print.visitChildNodes(*this);
    load_val = 0;
    // clang-format off
    constexpr const char *const output =
        "    lw a0, 0(sp)     ### print, pop the value from the stack to the first argument register 'a0'\n"
        "    addi sp, sp, 4\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), output);

    if(print_type == 1){
        // clang-format off
        constexpr const char *const call_print =
            "    jal ra, printInt # call function 'printInt'\n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), call_print);
    }
    else if(print_type == 2){
        // clang-format off
        constexpr const char *const call_print =
            "    jal ra, printInt # call function 'printReal'\n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), call_print);
    }
}

void CodeGenerator::visit(BinaryOperatorNode &p_bin_op) {
    p_bin_op.visitChildNodes(*this);

    // clang-format off
    constexpr const char *const output =
        "    lw t0, 0(sp) ### binary operation \n"
        "    addi sp, sp, 4 \n"
        "    lw t1, 0(sp) \n"
        "    addi sp, sp, 4 \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), output);
    
    if(strcmp(p_bin_op.getOpCString(),"+") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    add t0, t1, t0 # add\n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation);
    }
    else if(strcmp(p_bin_op.getOpCString(),"-") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    sub t0, t1, t0 # sub \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation);
    }
    else if(strcmp(p_bin_op.getOpCString(),"*") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    mul t0, t1, t0 #mul \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation);
    }
    else if(strcmp(p_bin_op.getOpCString(),"/") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    div t0, t1, t0 #div \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation);
    }
    else if(strcmp(p_bin_op.getOpCString(),"mod") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    rem t0, t1, t0 #mod \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation);
    }
    else if(strcmp(p_bin_op.getOpCString(),"<=") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    bgt t1, t0, C%d # <= \n"
            "    addi t0, x0, 1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "    j C%d\n"
            "C%d:   \n"
            "    addi t0, x0, -1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "C%d:   \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation, comp, comp+1, comp,comp+1);
        comp+=2;
    }
    else if(strcmp(p_bin_op.getOpCString(),"<") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    bge t1, t0, C%d # < \n"
            "    addi t0, x0, 1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "    j C%d\n"
            "C%d:   \n"
            "    addi t0, x0, -1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "C%d:   \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation, comp, comp+1, comp,comp+1);
        comp+=2;
    }
    else if(strcmp(p_bin_op.getOpCString(),">=") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    blt t1, t0, C%d # >= \n"
            "    addi t0, x0, 1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "    j C%d\n"
            "C%d:   \n"
            "    addi t0, x0, -1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "C%d:   \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation, comp, comp+1, comp,comp+1);
        comp+=2;
    }
    else if(strcmp(p_bin_op.getOpCString(),">") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    ble t1, t0, C%d # > \n"
            "    addi t0, x0, 1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "    j C%d\n"
            "C%d:   \n"
            "    addi t0, x0, -1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "C%d:   \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation, comp, comp+1, comp,comp+1);
        comp+=2;
    }
    else if(strcmp(p_bin_op.getOpCString(),"=") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    bne t1, t0, C%d # = \n"
            "    addi t0, x0, 1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "    j C%d\n"
            "C%d:   \n"
            "    addi t0, x0, -1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "C%d:   \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation, comp, comp+1, comp,comp+1);
        comp+=2;
    }
    else if(strcmp(p_bin_op.getOpCString(),"<>") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    beq t1, t0, C%d # <> \n"
            "    addi t0, x0, 1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "    j C%d\n"
            "C%d:   \n"
            "    addi t0, x0, -1 \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            "C%d:   \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation, comp, comp+1, comp,comp+1);
        comp+=2;
    }
    else if(strcmp(p_bin_op.getOpCString(),"and") == 0){
        // clang-format off
        constexpr const char *const operation =
            "    and t0, t0, t1 # and \n"
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation);
    }

}

void CodeGenerator::visit(UnaryOperatorNode &p_un_op) {
    p_un_op.visitChildNodes(*this);

    // clang-format off
    constexpr const char *const output =
        "    lw t0, 0(sp) ### unary operation \n"
        "    addi sp, sp, 4 \n"
        "    sub t0, x0, t0 # sub \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), output);
    
    // if(strcmp(p_un_op.getOpCString(),"-") == 0){
    //     // clang-format off
    //     constexpr const char *const operation =
    //         "    addi sp, sp, -4 \n"
    //         "    sw t0, 0(sp) \n"
    //         ;
    //     // clang-format on
    //     dumpInstructions(m_output_file.get(), operation);
    // }

    // if(strcmp(p_un_op.getOpCString(), "not") == 0){
    //     // clang-format off
    //     constexpr const char *const operation =
    //         "    beq t1, t0, L%d # not \n"
    //         ;
    //     // clang-format on
    //     dumpInstructions(m_output_file.get(), operation, label + 1);
    // }
    // else{
        // clang-format off
        constexpr const char *const operation =
            "    addi sp, sp, -4 \n"
            "    sw t0, 0(sp) \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), operation);
    //}
}

void CodeGenerator::visit(FunctionInvocationNode &p_func_invocation) {
    p_func_invocation.visitChildNodes(*this);

    // marker, function invocation node

    for(int i = p_func_invocation.getArguments().size() - 1; i >= 0;i--){
        // clang-format off
        constexpr const char *const argument =
            "    lw a%d, 0(sp) # pop the value from the stack to argument\n"
            "    addi sp, sp, 4\n"
            ;
        // clang-format on

        // clang-format off
        constexpr const char *const argument_more_than_8 =
            "    lw t%d, 0(sp) # pop the value from the stack to argument\n"
            "    addi sp, sp, 4\n"
            ;
        // clang-format on
        if(i > 7)dumpInstructions(m_output_file.get(), argument_more_than_8, i-8);
        else dumpInstructions(m_output_file.get(), argument, i);
    }

    // clang-format off
    constexpr const char *const output =
        "    jal ra, %s # call function '%s'\n"
        "    mv t0, a0\n"
        "    addi sp, sp, -4\n"
        "    sw t0, 0(sp)\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), output, p_func_invocation.getNameCString(), p_func_invocation.getNameCString());
}

void CodeGenerator::visit(VariableReferenceNode &p_variable_ref) {
    SymbolEntry *cur = m_symbol_manager_ptr->lookup(p_variable_ref.getNameCString());
    
    if(cur->getLevel() > 0){
        // clang-format off
        constexpr const char *const output_val =
            "    lw t0, %d(s0) ### variable reference, local variable\n"
            "    addi sp, sp, -4\n"
            "    sw t0, 0(sp)  # push %s\n"
            ;
        constexpr const char *const output_addr =
            "    addi t0, s0, %d ### variable reference, local variable\n"
            "    addi sp, sp, -4\n"
            "    sw t0, 0(sp)  # push %s\n"
            ;
        // clang-format on
        if(load_addr) {
            dumpInstructions(m_output_file.get(), output_addr, cur->on_stack, p_variable_ref.getNameCString());
            load_addr = 0;
        }
        else if (load_val){
            dumpInstructions(m_output_file.get(), output_val, cur->on_stack, p_variable_ref.getNameCString());
            load_val = 0;

            if(cur->getTypePtr()->isInteger() || cur->getTypePtr()->isPrimitiveInteger()){
                print_type = 1;
            }
            else if(cur->getTypePtr()->isBool() || cur->getTypePtr()->isPrimitiveBool()){
                print_type = 2;
            }
            
        }
        else dumpInstructions(m_output_file.get(), output_val, cur->on_stack, p_variable_ref.getNameCString());
    }
    else{
        // clang-format off
        constexpr const char *const output_val =
            "    la t0, %s ### variable reference, global variable\n"
            "    lw t1, 0(t0)\n"
            "    mv t0, t1\n"
            "    addi sp, sp, -4\n"
            "    sw t0, 0(sp)\n"
            ;
        constexpr const char *const output_addr =
            "    la t0, %s ### variable reference, global variable\n"
            "    addi sp, sp, -4\n"
            "    sw t0, 0(sp)\n"
            ;
        // clang-format on
        if(load_addr) {
            dumpInstructions(m_output_file.get(), output_addr, p_variable_ref.getNameCString());
            load_addr = 0;
        }
        else if(load_val) {
            dumpInstructions(m_output_file.get(), output_val, p_variable_ref.getNameCString());
            load_val = 0;

            if(cur->getTypePtr()->isInteger() || cur->getTypePtr()->isPrimitiveInteger()){
                print_type = 1;
            }
            else if(cur->getTypePtr()->isBool() || cur->getTypePtr()->isPrimitiveBool()){
                print_type = 2;
            }
        }
        else dumpInstructions(m_output_file.get(), output_val, p_variable_ref.getNameCString());

        p_variable_ref.visitChildNodes(*this);
    }  
}

void CodeGenerator::visit(AssignmentNode &p_assignment) {
    load_addr = 1;
    p_assignment.visitChildNodes(*this); 
    load_addr = 0;

    // clang-format off
    constexpr const char *const output =
        "    lw t0, 0(sp) ### assignment, give value\n"
        "    addi sp, sp, 4\n"
        "    lw t1, 0(sp)\n"
        "    addi sp, sp, 4\n"
        "    sw t0, 0(t1)\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), output);

}

void CodeGenerator::visit(ReadNode &p_read) {
    load_addr = 1;
    p_read.visitChildNodes(*this);
    load_addr = 0;

    // clang-format off
    constexpr const char *const output =
        "    jal ra, readInt ### read node\n"
        "    lw t0, 0(sp)\n"
        "    addi sp, sp, 4\n"
        "    sw a0, 0(t0)\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), output);
}

void CodeGenerator::visit(IfNode &p_if) {
    int cur_label = label;

    p_if.m_condition->accept(*this);
    // clang-format off 
    constexpr const char *const after_condition =
        "    lw t0, 0(sp) \n"
        "    addi sp, sp, 4 \n"
        "    addi t1, x0, 1\n"
        "    bne t0, t1, L%d\n"
        "L%d: \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), after_condition, cur_label + 1,cur_label);
    cur_label++;

    p_if.m_body->accept(*this);
    if (p_if.m_else_body) {
        // clang-format off 
        constexpr const char *const else_label =
            "    j L%d \n"
            "L%d: \n"
            ;
        // clang-format on
        dumpInstructions(m_output_file.get(), else_label, cur_label+1, cur_label);
        cur_label++;

        p_if.m_else_body->accept(*this);
    }

    // clang-format off
    constexpr const char *const if_label =
        "L%d: \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), if_label, cur_label);
    cur_label++;
    label = cur_label;
}

void CodeGenerator::visit(WhileNode &p_while) {
    int cur_label = label;
    // clang-format off 
    constexpr const char *const while_condition =
        "L%d: \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), while_condition, cur_label);
    cur_label++;
    label = cur_label;

    p_while.m_condition->accept(*this);
    // not sure
    // clang-format off 
    constexpr const char *const if_label =
        "    lw t0, 0(sp) \n"
        "    addi sp, sp, 4 \n"
        "    addi t1, x0, 1\n"
        "    bne t0, t1, L%d\n"
        "L%d: \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), if_label, cur_label+1,cur_label);
    
    p_while.m_body->accept(*this);
    // clang-format off 
    constexpr const char *const while_label =
        "    j L%d \n"
        "L%d: \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), while_label, cur_label-1, cur_label+1);
    cur_label+=2;
    label = cur_label;
}

void CodeGenerator::visit(ForNode &p_for) {
    // Reconstruct the hash table for looking up the symbol entry
    m_symbol_manager_ptr->reconstructHashTableFromSymbolTable(
        p_for.getSymbolTable());

    int cur_label = label;
    const int loop_var_offset = offset;

    p_for.m_loop_var_decl->accept(*this);
    p_for.m_init_stmt->accept(*this);

    // SymbolEntry *cur = m_symbol_manager_ptr->lookup();
    //     cur->on_stack = offset;

    // clang-format off 
    constexpr const char *const for_start_label =
        "L%d:               ### for start\n"
        "    lw t0, %d(s0)\n"
        "    addi sp, sp, -4\n"
        "    sw t0, 0(sp) \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), for_start_label, cur_label, loop_var_offset);
    cur_label++;
    label = cur_label;

    p_for.m_end_condition->accept(*this);

    // clang-format off 
    constexpr const char *const for_end_label =
        "    lw t0, 0(sp) ### for end condition\n"
        "    addi sp, sp, 4\n"
        "    lw t1, 0(sp)\n"
        "    addi sp, sp, 4\n"
        "    bge t1, t0, L%d\n"
        "L%d: \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), for_end_label, cur_label+1, cur_label);
    cur_label+=2;
    label = cur_label;

    p_for.m_body->accept(*this);

    // clang-format off 
    constexpr const char *const for_compound_statement_end =
        "    addi t0, s0, %d   ### for compound statement end\n"
        "    addi sp, sp, -4    \n"
        "    sw t0, 0(sp)       \n"
        "    lw t0, %d(s0)     \n"
        "    addi sp, sp, -4    \n"
        "    sw t0, 0(sp)       \n"
        "    li t0, 1           \n"
        "    addi sp, sp, -4    \n"
        "    sw t0, 0(sp)       \n"
        "    lw t0, 0(sp)       \n"
        "    addi sp, sp, 4     \n"
        "    lw t1, 0(sp)       \n"
        "    addi sp, sp, 4     \n"
        "    add t0, t1, t0     \n"
        "    addi sp, sp, -4    \n"
        "    sw t0, 0(sp)       \n"
        "    lw t0, 0(sp)       \n"
        "    addi sp, sp, 4     \n"
        "    lw t1, 0(sp)       \n"
        "    addi sp, sp, 4     \n"
        "    sw t0, 0(t1)       \n"
        "    j L%d              \n"
        "L%d: \n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), for_compound_statement_end, loop_var_offset, loop_var_offset, cur_label-3, cur_label-1);
    // cur_label++;
    // label = cur_label;

    // p_for.visitChildNodes(*this);

    // Remove the entries in the hash table
    m_symbol_manager_ptr->removeSymbolsFromHashTable(p_for.getSymbolTable());
}

void CodeGenerator::visit(ReturnNode &p_return) {
    p_return.visitChildNodes(*this);
    // clang-format off
    constexpr const char *const output =
        "    lw t0, 0(sp) ### return node\n"
        "    addi sp, sp, 4\n"
        "    mv a0, t0\n"
        ;
    // clang-format on
    dumpInstructions(m_output_file.get(), output);
}
