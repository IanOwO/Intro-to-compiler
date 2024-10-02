#include "sema/SemanticAnalyzer.hpp"
#include "visitor/AstNodeInclude.hpp"

void SemanticAnalyzer::visit(ProgramNode &p_program) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    SymbolTable* sb = new SymbolTable;
    global_table = sb;
    this->level = 0;
    sb->addSymbol(p_program.m_name,"program",this->level,"void","");
    this->manager.pushScope(sb);
    cur_table = this->manager.tables.top();

    p_program.visitChildNodes(*this);

    this->manager.popScope();
    
    
}

void SemanticAnalyzer::visit(DeclNode &p_decl) {
    p_decl.visitChildNodes(*this);
}

void SemanticAnalyzer::visit(VariableNode &p_variable) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    cur_table = this->manager.tables.top();
    int input_success = 0;
    int not_valid_array = 0;
    if (redeclaration(p_variable.getLocation().line,p_variable.getLocation().col,p_variable.m_name)){
        input_success = 1;
        if(this->for_is_decl)this->for_no_pop = 1;
    }

    if (p_variable.m_type->m_dimensions.size() > 0 && array_index_less_than_0(p_variable)) {
        not_valid_array = 1;
    }

    if (this->for_is_decl && !input_success) {
        this->for_parameter.push_back(p_variable.m_name);
        cur_table->addSymbol(p_variable.getNameCString(),"loop_var",this->level ,p_variable.m_type,"");
        input_success = 1;
        cur_table->entries.back().not_valid_entry = not_valid_array;
    }

    if (this->func_is_parameter && !input_success) {
        cur_table->addSymbol(p_variable.getNameCString(),"parameter",this->level ,p_variable.m_type,"");
        input_success = 1;
        cur_table->entries.back().not_valid_entry = not_valid_array;
    }

    if(!input_success){
        cur_table->addSymbol(p_variable.getNameCString(),"variable",this->level ,p_variable.m_type,"");
        cur_table->entries.back().not_valid_entry = not_valid_array;
    }
    
    p_variable.visitChildNodes(*this);

    //fprintf(stderr,"variable name: %s\n",p_variable.getNameCString());
}

void SemanticAnalyzer::visit(ConstantValueNode &p_constant_value) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    cur_table = this->manager.tables.top();
    
    // if(strcmp(p_constant_value.getTypeSharedPtr()->getPTypeCString(),"integer") == 0 && this->variable_ref_using){
    //     this->array_dimention.push_back(p_constant_value.getConstantValueCString());
    // }
    if(is_arr){
        if(strcmp(p_constant_value.getTypeSharedPtr()->getPTypeCString(),"integer") == 0){
            this->array_dimention.push_back(p_constant_value.getConstantValueCString());
        }
        else if(arr_index_not_valid == 0){
            // fprintf(stderr," hghghghg:%s",p_constant_value.getTypeSharedPtr()->getPTypeCString());
            arr_index_not_valid = 1;
        }
    }

    if(this->for_is_first){
        this->for_first = p_constant_value.getConstantValueCString();
        return;
    }
    if(this->for_is_second){
        this->for_second = p_constant_value.getConstantValueCString();
        return;
    }
    if(this->variable_ref_using || this->binary_using || this->unary_using || this->func_invocation_using || this->assignment_using){
        // fprintf(stderr,"const value:%s\n",p_constant_value.getConstantValueCString());
        return;
    }

    p_constant_value.settype(p_constant_value.getConstantValueCString());
    if(cur_table->entries.empty())return;
    if(cur_table->entries.back().kind == "variable"){
        cur_table->entries.back().attribute = p_constant_value.getConstantValueCString();
        cur_table->entries.back().kind = "constant";
    }

}

void SemanticAnalyzer::visit(FunctionNode &p_function) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    SymbolTable* sb = new SymbolTable;
    cur_table = this->manager.tables.top();
    
    if(redeclaration(p_function.getLocation().line,p_function.getLocation().col,p_function.m_name)){}
    else {
        // fprintf(stderr,"protoptye:%s",p_function.getParameter().c_str());
        cur_table->addSymbol(p_function.m_name,"function",this->level,p_function.m_ret_type->getPTypeCString(),p_function.getParameter().c_str());
    }
    this->level++;
    sb->func_name = p_function.getNameCString();
    this->manager.pushScope(sb);

    this->func_is_parameter = 1;
    auto visit_ast_node = [&](auto &ast_node) { ast_node->accept(*this); };
    for_each(p_function.m_parameters.begin(), p_function.m_parameters.end(), visit_ast_node);
    this->func_is_parameter = 0;

    if (p_function.m_body) {
        this->func_is_compound = 1;
        visit_ast_node(p_function.m_body);
        this->func_is_compound = 0;
    }

    this->manager.popScope();
    this->level--;
}

void SemanticAnalyzer::visit(CompoundStatementNode &p_compound_statement) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    SymbolTable* sb = new SymbolTable;
    cur_table = this->manager.tables.top();

    if (!this->func_is_compound){
        this->level++;
        //sb->addSymbol("","",this->level,"","");
        this->manager.pushScope(sb);
        cur_table = this->manager.tables.top();

        p_compound_statement.visitChildNodes(*this);

        this->manager.popScope();
        this->level--;
    }
    else{
        this->func_is_compound = 0;
        p_compound_statement.visitChildNodes(*this);
    }
}

void SemanticAnalyzer::visit(PrintNode &p_print) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    // this->print_using = 1;
    // is_arr = 0;
    //fprintf(stderr,"start\n");

    p_print.visitChildNodes(*this);
    this->print_using = 0;

    //fprintf(stderr,"in print node\n");
    if(p_print.m_target == nullptr){
        //fprintf(stderr,"nullptr");
        return;
    }
    std::string the_type;
    if(p_print.m_target->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else the_type = p_print.m_target->node_type->getPTypeCString();
    //fprintf(stderr,"the type:%s\n",the_type.c_str());

    if(the_type == "integer" || the_type == "real" || the_type == "boolean" || the_type == "string" || the_type == "void"){}
    else{
        fprintf(stderr,"<Error> Found in line %u, column %u: expression of print statement must be scalar type\n",p_print.m_target->getLocation().line,p_print.m_target->getLocation().col);
        fprintf(stderr,"    %s\n",this->src[p_print.m_target->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_print.m_target->getLocation().col,'^');
        this->sematic_error = 1;
    }

}

void SemanticAnalyzer::visit(BinaryOperatorNode &p_bin_op) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    binary_using++;
    p_bin_op.visitChildNodes(*this);
    binary_using--;

    std::string op = p_bin_op.getOpCString();
    if(p_bin_op.m_left_operand->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else binary_type_first = p_bin_op.m_left_operand->node_type->getPTypeCString();
    
    if(p_bin_op.m_right_operand->node_type == nullptr) {
        //fprintf(stderr,"rigft is null\n");
        return;
    }
    else binary_type_second = p_bin_op.m_right_operand->node_type->getPTypeCString();

    //fprintf(stderr,"type1:%s,op:%s,type2:%s\n",binary_type_first.c_str(),op.c_str(),binary_type_second.c_str());
    if(op == "+" || op == "-" || op == "*" || op == "/"){
        int first_past = 0;
        int second_past = 0;
        int string_add = 0;
        if(binary_type_first == "integer"){
            first_past = 1;
        }
        if(binary_type_first == "real"){
            first_past = 2;
        }
        if(binary_type_second == "integer"){
            second_past = 1;
        }
        if(binary_type_second == "real"){
            second_past = 2;
        }
        if(binary_type_first == "string" && binary_type_second == "string" && op == "+"){
            string_add = 1;
        }
        if((!first_past || !second_past) && !string_add){
            fprintf(stderr,"<Error> Found in line %u, column %u: invalid operands to binary operator '%s' ('%s' and '%s')\n"
                    ,p_bin_op.getLocation().line,p_bin_op.getLocation().col,op.c_str(),binary_type_first.c_str(),binary_type_second.c_str());
            fprintf(stderr,"    %s\n",this->src[p_bin_op.getLocation().line]);
            fprintf(stderr,"    %*c\n",p_bin_op.getLocation().col,'^');
            this->sematic_error = 1;
        }
        else{
            // fprintf(stderr,"set type 1:%d,2:%d\n",first_past,second_past);
            if(string_add)p_bin_op.settype("string"); // marker, need modify its type to string
            else if(first_past == 2 || second_past == 2)p_bin_op.settype("real"); // marker, need to modify its type to real
            else if(first_past == 1 && second_past == 1)p_bin_op.settype("integer"); // marker, need to modify its type to int
        }
    }
    if(op == "mod"){
        int first_past = 0;
        int second_past = 0;
        if(binary_type_first == "integer"){
            first_past = 1;
        }
        if(binary_type_second == "integer"){
            second_past = 1;
        }
        if((!first_past || !second_past)){
            fprintf(stderr,"<Error> Found in line %u, column %u: invalid operands to binary operator '%s' ('%s' and '%s')\n"
                    ,p_bin_op.getLocation().line,p_bin_op.getLocation().col,op.c_str(),binary_type_first.c_str(),binary_type_second.c_str());
            fprintf(stderr,"    %s\n",this->src[p_bin_op.getLocation().line]);
            fprintf(stderr,"    %*c\n",p_bin_op.getLocation().col,'^');
            this->sematic_error = 1;
        }
        else{
            p_bin_op.settype("integer");
        }
    }
    if(op == "and" || op == "or"){
        int first_past = 0;
        int second_past = 0;
        if(binary_type_first == "boolean"){
            first_past = 1;
        }
        if(binary_type_second == "boolean"){
            second_past = 1;
        }
        if((!first_past || !second_past)){
            fprintf(stderr,"<Error> Found in line %u, column %u: invalid operands to binary operator '%s' ('%s' and '%s')\n"
                    ,p_bin_op.getLocation().line,p_bin_op.getLocation().col,op.c_str(),binary_type_first.c_str(),binary_type_second.c_str());
            fprintf(stderr,"    %s\n",this->src[p_bin_op.getLocation().line]);
            fprintf(stderr,"    %*c\n",p_bin_op.getLocation().col,'^');
            this->sematic_error = 1;
        }
        else{
            p_bin_op.settype("boolean");
        }
        
    }
    if(op == "<" || op == "<=" || op == "=" || op == ">=" || op == ">" || op == "<>"){
        int first_past = 0;
        int second_past = 0;
        if(binary_type_first == "integer" || binary_type_first == "real"){
            first_past = 1;
        }
        if(binary_type_second == "integer" || binary_type_second == "real"){
            second_past = 1;
        }
        if((!first_past || !second_past)){
            fprintf(stderr,"<Error> Found in line %u, column %u: invalid operands to binary operator '%s' ('%s' and '%s')\n"
                    ,p_bin_op.getLocation().line,p_bin_op.getLocation().col,op.c_str(),binary_type_first.c_str(),binary_type_second.c_str());
            fprintf(stderr,"    %s\n",this->src[p_bin_op.getLocation().line]);
            fprintf(stderr,"    %*c\n",p_bin_op.getLocation().col,'^');
            this->sematic_error = 1;
        }
        else{
            p_bin_op.settype("boolean");
        }
    }
}

void SemanticAnalyzer::visit(UnaryOperatorNode &p_un_op) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    
    this->unary_using = 1;
    p_un_op.visitChildNodes(*this);
    this->unary_using = 0;

    std::string op = p_un_op.getOpCString();
    //fprintf(stderr,"pass here\n");
    std::string the_type;
    if(p_un_op.m_operand->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else the_type = p_un_op.m_operand->node_type->getPTypeCString();
    //fprintf(stderr,"op:%s,type:%s\n",op.c_str(),the_type.c_str());
    if (op == "not" && the_type != "boolean"){
        fprintf(stderr,"<Error> Found in line %u, column %u: invalid operand to unary operator '%s' ('%s')\n"
                    ,p_un_op.getLocation().line,p_un_op.getLocation().col,op.c_str(),the_type.c_str());
        fprintf(stderr,"    %s\n",this->src[p_un_op.getLocation().line]);
        fprintf(stderr,"    %*c\n",p_un_op.getLocation().col,'^');
        this->sematic_error = 1;
    }
    else{
        p_un_op.settype("boolean");
    }
    if (op == "-"){
        if(the_type == "integer" || the_type == "real"){
            p_un_op.settype(p_un_op.node_type->getPTypeCString());
        }
        else{
            fprintf(stderr,"<Error> Found in line %u, column %u: invalid operand to unary operator '%s' ('%s')\n"
                        ,p_un_op.getLocation().line,p_un_op.getLocation().col,op.c_str(),the_type.c_str());
            fprintf(stderr,"    %s\n",this->src[p_un_op.getLocation().line]);
            fprintf(stderr,"    %*c\n",p_un_op.getLocation().col,'^');
            this->sematic_error = 1;
        }
    }
    

}

void SemanticAnalyzer::visit(FunctionInvocationNode &p_func_invocation) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    func_invocation_using = 1;
    p_func_invocation.visitChildNodes(*this);
    func_invocation_using = 0;
    
    SymbolEntry* entry = global_table->find_entry(p_func_invocation.m_name);
    if(function_ref(p_func_invocation)){
        return;
    }
    
    //fprintf(stderr,"name:%s,parameter:%s,parameter size:%lu\n",entry->name.c_str(),entry->attribute.c_str(),entry->parameter_.size());
    // if(entry->ptype == nullptr){
    //     fprintf(stderr,"this sis nullptr\n");
    // }
    // else{
    //     fprintf(stderr,"'type:%s\n",entry->type.c_str());
    // }
    if(entry->parameter_.size() != p_func_invocation.m_args.size()){
        fprintf(stderr,"<Error> Found in line %u, column %u: too few/much arguments provided for function '%s'\n",p_func_invocation.getLocation().line,p_func_invocation.getLocation().col,p_func_invocation.getNameCString());
        fprintf(stderr,"    %s\n",this->src[p_func_invocation.getLocation().line]);
        fprintf(stderr,"    %*c\n",p_func_invocation.getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }

    for(unsigned int i =0 ;i < p_func_invocation.m_args.size();i++){
        if(p_func_invocation.m_args[i]->node_type == nullptr) return;
    }
    for(unsigned int i =0 ;i < p_func_invocation.m_args.size();i++){
        std::string the_type = p_func_invocation.m_args[i]->node_type->getPTypeCString();
        if(the_type != entry->parameter_[i]) {
            fprintf(stderr,"<Error> Found in line %u, column %u: incompatible type passing '%s' to parameter of type '%s'\n",p_func_invocation.m_args[i]->getLocation().line,p_func_invocation.m_args[i]->getLocation().col,the_type.c_str(),entry->parameter_[i].c_str());
            fprintf(stderr,"    %s\n",this->src[p_func_invocation.m_args[i]->getLocation().line]);
            fprintf(stderr,"    %*c\n",p_func_invocation.m_args[i]->getLocation().col,'^');
            this->sematic_error = 1;
            return;
        }
    }
    
    
    // //fprintf(stderr,"functioninvovarion:%s\n",p_func_invocation.getNameCString());
    p_func_invocation.settype(entry->type);
}

void SemanticAnalyzer::visit(VariableReferenceNode &p_variable_ref) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to    
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    
    this->variable_ref_using = 1;
    p_variable_ref.visitChildNodes(*this);
    this->variable_ref_using = 0;

    cur_table = manager.tables.top();
    SymbolEntry* cur_entry = cur_table->find_entry(p_variable_ref.getNameCString());
    SymbolEntry* global_entry = global_table->find_entry(p_variable_ref.getNameCString());

    if(varable_ref(p_variable_ref)){
        //fprintf(stderr,"<Error> Found in line %u, column %u: there is an over array subscript on '%s'\n",p_variable_ref.getLocation().line,p_variable_ref.getLocation().col,p_variable_ref.m_name.c_str());
        return;
    }
    // fprintf(stderr,"<check> Found in line %u, column %u: there is an over array subscript on '%s'\n",p_variable_ref.getLocation().line,p_variable_ref.getLocation().col,p_variable_ref.m_name.c_str());
    // fprintf(stderr,"<check> cur entry name '%s'\n",cur_entry->name.c_str());

    // fprintf(stderr,"<check> p_variable_size:%lu,cur_entry:%d\n",p_variable_ref.m_indices.size(),-123);
    if(cur_entry != nullptr && p_variable_ref.m_indices.size() > cur_entry->ptype->m_dimensions.size()){
        fprintf(stderr,"<Error> Found in line %u, column %u: there is an over array subscript on '%s'\n",p_variable_ref.getLocation().line,p_variable_ref.getLocation().col,p_variable_ref.m_name.c_str());
        fprintf(stderr,"    %s\n",this->src[p_variable_ref.getLocation().line]);
        fprintf(stderr,"    %*c\n",p_variable_ref.getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }
    else if(!p_variable_ref.m_indices.empty()){
        //fprintf(stderr," hghghghg:%lu\n",p_variable_ref.m_indices.size());
        // fprintf(stderr,"name:%s,type:%lu\n",cur_entry->name.c_str(),p_variable_ref.node_type->m_dimensions.size());
        for(unsigned int i = 0;i < p_variable_ref.m_indices.size();i++){
            if(p_variable_ref.m_indices[i]->node_type == nullptr)fprintf(stderr,"nullptr)");
            
            //(stderr,"type :%s\n",p_variable_ref.m_indices[i]->node_type->getPTypeCString());
            std::string the_type = p_variable_ref.m_indices[i]->node_type->getPTypeCString();
            if(the_type != "integer"){
                fprintf(stderr,"<Error> Found in line %u, column %u: index of array reference must be an integer\n",p_variable_ref.m_indices[i]->getLocation().line,p_variable_ref.m_indices[i]->getLocation().col);
                fprintf(stderr,"    %s\n",this->src[p_variable_ref.m_indices[i]->getLocation().line]);
                fprintf(stderr,"    %*c\n",p_variable_ref.m_indices[i]->getLocation().col,'^');
                this->sematic_error = 1;
                return;
            }
        }
    }
    if(cur_entry != nullptr){
        //fprintf(stderr,"LOCAL name:%s,type:%s\n",cur_entry->name.c_str(),cur_entry->type.c_str());
        std::stringstream ss;
        std::string type_str;
        ss<<cur_entry->type;
        ss>>type_str;
        //fprintf(stderr,"set type:%s\n",type_str.c_str());
        p_variable_ref.settype(type_str);
        p_variable_ref.dim_modify(cur_entry->type);
    }
    else if(global_entry != nullptr){
        //fprintf(stderr,"GLOBAL name:%s,type:%s\n",global_entry->name.c_str(),global_entry->type.c_str());
        std::stringstream ss;
        std::string type_str;
        ss<<global_entry->type;
        ss>>type_str;
        //fprintf(stderr,"set type:%s\n",type_str.c_str());
        p_variable_ref.settype(type_str);
        p_variable_ref.dim_modify(global_entry->type);
    }
}

void SemanticAnalyzer::visit(AssignmentNode &p_assignment) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    assignment_using = 1;
    p_assignment.visitChildNodes(*this);
    assignment_using = 0;

    cur_table = manager.tables.top();
    SymbolEntry* cur_entry = cur_table->find_entry(p_assignment.m_lvalue->getNameCString());
    std::string leftname = p_assignment.m_lvalue->getNameCString();
    std::string the_type;
    if(p_assignment.m_lvalue->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else the_type = p_assignment.m_lvalue->node_type->getPTypeCString();

    if(p_assignment.m_lvalue->node_type->m_dimensions.size() > 0){
        fprintf(stderr,"<Error> Found in line %u, column %u: array assignment is not allowed\n",p_assignment.m_lvalue->getLocation().line,p_assignment.m_lvalue->getLocation().col);
        fprintf(stderr,"    %s\n",this->src[p_assignment.m_lvalue->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_assignment.m_lvalue->getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }
    if(cur_entry->kind == "constant"){
        fprintf(stderr,"<Error> Found in line %u, column %u: cannot assign to variable '%s' which is a constant\n",p_assignment.m_lvalue->getLocation().line,p_assignment.m_lvalue->getLocation().col,cur_entry->name.c_str());
        fprintf(stderr,"    %s\n",this->src[p_assignment.m_lvalue->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_assignment.m_lvalue->getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }
    if(p_assignment.m_expr->node_type->m_dimensions.size() > 0){
        fprintf(stderr,"<Error> Found in line %u, column %u: array assignment is not allowed\n",p_assignment.m_expr->getLocation().line,p_assignment.m_expr->getLocation().col);
        fprintf(stderr,"    %s\n",this->src[p_assignment.m_expr->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_assignment.m_expr->getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }
    std::string exp_type = p_assignment.m_expr->node_type->getPTypeCString();
    if(exp_type != the_type){
        if(exp_type == "integer" && the_type == "real"){}
        else {
            fprintf(stderr,"<Error> Found in line %u, column %u: assigning to '%s' from incompatible type '%s'\n"
                ,p_assignment.getLocation().line,p_assignment.getLocation().col,the_type.c_str(),exp_type.c_str());
            fprintf(stderr,"    %s\n",this->src[p_assignment.getLocation().line]);
            fprintf(stderr,"    %*c\n",p_assignment.getLocation().col,'^');
            this->sematic_error = 1;
            return;
        }
    }

}

void SemanticAnalyzer::visit(ReadNode &p_read) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    this->read_using = 1;
    p_read.visitChildNodes(*this);
    this->read_using = 1;
    std::string the_type;
    if(p_read.m_target->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else the_type = p_read.m_target->node_type->getPTypeCString();
    // fprintf(stderr,"the type:%s\n",the_type.c_str());

    if(the_type == "integer" || the_type == "real" || the_type == "boolean" || the_type == "string" || the_type == "void"){}
    else{
        fprintf(stderr,"<Error> Found in line %u, column %u: variable reference of read statement must be scalar type\n",p_read.m_target->getLocation().line,p_read.m_target->getLocation().col);
        fprintf(stderr,"    %s\n",this->src[p_read.m_target->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_read.m_target->getLocation().col,'^');
        this->sematic_error = 1;
    }
}

void SemanticAnalyzer::visit(IfNode &p_if) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    p_if.visitChildNodes(*this);
    
    std::string the_type;
    if(p_if.m_condition->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else the_type = p_if.m_condition->node_type->getPTypeCString();

    if(the_type != "boolean"){
        fprintf(stderr,"<Error> Found in line %u, column %u: the expression of condition must be boolean type\n",p_if.m_condition->getLocation().line,p_if.m_condition->getLocation().col);
        fprintf(stderr,"    %s\n",this->src[p_if.m_condition->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_if.m_condition->getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }
}

void SemanticAnalyzer::visit(WhileNode &p_while) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    p_while.visitChildNodes(*this);

    std::string the_type;
    if(p_while.m_condition->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else the_type = p_while.m_condition->node_type->getPTypeCString();

    if(the_type != "boolean"){
        fprintf(stderr,"<Error> Found in line %u, column %u: the expression of condition must be boolean type\n",p_while.m_condition->getLocation().line,p_while.m_condition->getLocation().col);
        fprintf(stderr,"    %s\n",this->src[p_while.m_condition->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_while.m_condition->getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }
}

void SemanticAnalyzer::visit(ForNode &p_for) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    SymbolTable* sb = new SymbolTable;
    this->manager.pushScope(sb);
    cur_table = this->manager.tables.top();
    this->level++;
    this->for_using++;
    
    this->for_is_decl = 1;
    p_for.m_loop_var_decl->accept(*this);
    this->for_is_decl = 0;

    if(!this->for_no_pop){
        this->for_is_first = 1;
        p_for.m_init_stmt->accept(*this);
        this->for_is_first = 0;
        this->for_is_second = 1;
        p_for.m_end_condition->accept(*this);
        this->for_is_second = 0;

        if(upper_lower_check(p_for.getLocation().line,p_for.getLocation().col)) { }
    }
    p_for.m_body->accept(*this);

    this->manager.popScope();
    this->level--;
    this->for_using--;
    if(!this->for_no_pop){
        this->for_parameter.pop_back();
        this->for_no_pop = 0;
    }
    
}

void SemanticAnalyzer::visit(ReturnNode &p_return) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
    p_return.visitChildNodes(*this);

    SymbolTable *cur_table  = this->manager.tables.top();
    if(cur_table->func_name == ""){
        fprintf(stderr,"<Error> Found in line %u, column %u: program/procedure should not return a value\n"
            ,p_return.getLocation().line,p_return.getLocation().col);
        fprintf(stderr,"    %s\n",this->src[p_return.getLocation().line]);
        fprintf(stderr,"    %*c\n",p_return.getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }

    std::string the_type;
    if(p_return.m_ret_val->node_type == nullptr){
        //fprintf(stderr,"left is null,,\n");
        return;
    }
    else the_type = p_return.m_ret_val->node_type->getPTypeCString();

    std::string def_type = global_table->find_entry(cur_table->func_name)->type;
    if(def_type != the_type){
        fprintf(stderr,"<Error> Found in line %u, column %u: return '%s' from a function with return type '%s'\n"
            ,p_return.m_ret_val->getLocation().line,p_return.m_ret_val->getLocation().col,the_type.c_str(),def_type.c_str());
        fprintf(stderr,"    %s\n",this->src[p_return.m_ret_val->getLocation().line]);
        fprintf(stderr,"    %*c\n",p_return.m_ret_val->getLocation().col,'^');
        this->sematic_error = 1;
        return;
    }
}

bool SemanticAnalyzer::redeclaration(uint32_t line,uint32_t col,std::string check_name) {
    int error = 0;
    if(this->for_using && this->for_parameter.size() != 0 ) {
        for (unsigned int i = 0;i < this->for_parameter.size();i++){
            if(this->for_parameter[i] == check_name) {
                this->sematic_error = 1;
                error = 1;
            }
        }
    }
    for (unsigned int i = 0;i < this->cur_table->entries.size();i++){
        if(this->cur_table->entries[i].name == check_name){
            this->sematic_error = 1;
            error = 1;
        }
    }
    if (error) {
        fprintf(stderr,"<Error> Found in line %u, column %u: symbol '%s' is redeclared\n",line,col,check_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    else return 0;
}

bool SemanticAnalyzer::array_index_less_than_0(VariableNode &node){
    int error = 0;
    for(unsigned int i = 0;i < node.m_type->m_dimensions.size();i++){
        if(node.m_type->m_dimensions[i] <= 0){
            this->sematic_error = 1;
            error = 1;
        }
    }
    if (error) {
        fprintf(stderr,"<Error> Found in line %u, column %u: '%s' declared as an array with an index that is not greater than 0\n",node.getLocation().line,node.getLocation().col,node.getNameCString());
        fprintf(stderr,"    %s\n",this->src[node.getLocation().line]);
        fprintf(stderr,"    %*c\n",node.getLocation().col,'^');
        this->sematic_error = 1;
        return 1;
    }
    else return 0;
}

bool SemanticAnalyzer::upper_lower_check(u_int32_t line,u_int32_t col){
    int error = 0;
    if(atoi(this->for_first) > atoi(this->for_second)){
        this->sematic_error = 1;
        error = 1;
    }
    if (error) {
        fprintf(stderr,"<Error> Found in line %u, column %u: the lower bound and upper bound of iteration count must be in the incremental order\n",line,col);
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    else return 0;
}

bool SemanticAnalyzer::varable_ref(VariableReferenceNode &var_node){
    std::string var_name = var_node.getNameCString();
    int line = var_node.getLocation().line;
    int col = var_node.getLocation().col;

    int global_undefined = 1; // did not define
    int global_nonvariable = 1; // is function
    int global_not_valid_var = 0; // not valid variable
    int global_is_function = 0;

    int read_const_loopvar = 0; // read node, const or loop variable
    int assignment_loopvar = 0;
    
    for(unsigned int i = 0;i < global_table->entries.size();i++){
        //fprintf(stderr,"check:%s, cur table entry:%s, cur table entry kind:%s\n",var_name.c_str(),global_table->entries[i].name.c_str(),global_table->entries[i].kind.c_str());
        if (global_table->entries[i].name == var_name) {
            if(global_table->entries[i].not_valid_entry){
                global_not_valid_var = 1;
                continue;
            }
            global_not_valid_var = 0;
            global_undefined = 0;
            if(global_table->entries[i].kind == "function"){
                global_is_function = 1;
                // fprintf(stderr,"global table size:%lu\n",global_table->entries[i].parameter_.size());
                for(unsigned int j = 0;j < global_table->entries[i].parameter_.size();j++){
                    std::string tmp = global_table->entries[i].parameter_[j];
                    //fprintf(stderr,"global table size:%s\n",tmp.c_str());
                    func_parameter.push_back(tmp);
                }
                // fprintf(stderr,"check fun_parameter size:%lu\n",func_parameter.size());
                break;
            }
            // fprintf(stderr,"check:%s, \n",cur_table->entries[i].ptype->getPTypeCString())
            break;
        }
    }
    //fprintf(stderr,"function name:%s,function unvocation:%d\n",var_name.c_str(),this->func_invocation_using);
    if(global_undefined == 1 && !global_not_valid_var && this->func_invocation_using == 2){
        if(this->func_invocation_using == 2)this->func_invocation_using--;
        fprintf(stderr,"<Error> Found in line %u, column %u: use of undeclared symbol '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    if(global_is_function == 0 && !global_not_valid_var && this->func_invocation_using == 2){
        if(this->func_invocation_using == 2)this->func_invocation_using--;
        fprintf(stderr,"<Error> Found in line %u, column %u: use of non-function symbol '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    
    int undefined = 1; // did not define
    int nonvariable = 1; // is function
    int not_valid_var = 0; // not valid variable
    int arr_dimension = 0;
    int is_function = 0;
    for(unsigned int i = 0;i < cur_table->entries.size();i++){
        //fprintf(stderr,"check:%s, cur table entry:%s, cur table entry kind:%s\n",var_name.c_str(),cur_table->entries[i].name.c_str(),cur_table->entries[i].kind.c_str());
        if (cur_table->entries[i].name == var_name) {
            if(cur_table->entries[i].not_valid_entry){
                not_valid_var = 1;
                continue;
            }
            not_valid_var = 0;
            undefined = 0;
            if(cur_table->entries[i].kind == "variable" || cur_table->entries[i].kind == "loop_var" || cur_table->entries[i].kind == "constant"){
                nonvariable = 0;
                if(this->read_using && (cur_table->entries[i].kind == "loop_var" || cur_table->entries[i].kind == "constant"))read_const_loopvar = 1;
                if(this->read_using && cur_table->entries[i].kind == "loop_var")assignment_loopvar = 1;
                //break;
            }
            else if(cur_table->entries[i].kind == "function"){
                is_function = 1;
                // fprintf(stderr,"curtable size:%lu\n",cur_table->entries[i].parameter_.size());
                for(unsigned int j = 0;j < cur_table->entries[i].parameter_.size();j++){
                    func_parameter.push_back(cur_table->entries[i].parameter_[j]);
                }
                break;
            }
            // fprintf(stderr,"check:%s, \n",cur_table->entries[i].ptype->getPTypeCString());

            if(cur_table->entries[i].ptype->m_dimensions.size() > 0 ){
                arr_dimension = cur_table->entries[i].ptype->m_dimensions.size();
                array_ptype_ptr = cur_table->entries[i].ptype;
                std::stringstream ss;
                ss << cur_table->entries[i].ptype->getPTypeCString();
                /*if(this->binary_using_first){
                    ss >> binary_type_first;
                }
                if(this->binary_using_second){
                    ss >> binary_type_second;
                }*/
                // if(this->binary_using){
                //     var_node.settype(cur_table->entries[i].ptype->m_type_string);
                // }
                // if(this->unary_using){
                //     ss >> unary_type;
                // }
            }
            else{
                arr_dimension = 0;
            }
            break;
        }
    }

    if(this->for_using){
        for(unsigned int i = 0;i < for_parameter.size();i++){
            if(var_name == for_parameter[i]){
                undefined = 0;
                nonvariable = 0;
                not_valid_var = 0;
                if(this->read_using)read_const_loopvar = 1;
                if(this->assignment_using)assignment_loopvar = 1;
            }
        }
    }
    is_arr = arr_dimension;
    if(not_valid_var) {
        // fprintf(stderr,"inside not valid var\n");
        return 1;
    }
    if(cur_table->func_name == var_name){
        undefined = 0;
    }
    if(this->func_invocation_using == 2 && (is_function == 1 || global_is_function == 1)){
        this->func_invocation_using=1;
        return 0;
    }

    if(undefined == 1 && !not_valid_var){
        fprintf(stderr,"<Error> Found in line %u, column %u: use of undeclared symbol '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    if(nonvariable == 1 && !not_valid_var){
        fprintf(stderr,"<Error> Found in line %u, column %u: use of non-variable symbol '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    if(is_function == 0 && !not_valid_var && this->func_invocation_using == 2){
        if(this->func_invocation_using == 2)this->func_invocation_using--;
        fprintf(stderr,"<Error> Found in line %u, column %u: use of non-function symbol '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    if(read_const_loopvar && this->read_using && !this->for_is_first && !this->for_is_second){
        fprintf(stderr,"<Error> Found in line %u, column %u: variable reference of read statement cannot be a constant or loop variable\n",line,col);
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    if(assignment_loopvar && this->assignment_using && !this->for_is_first && !this->for_is_second){
        fprintf(stderr,"<Error> Found in line %u, column %u: the value of loop variable cannot be modified inside the loop body\n",line,col);
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    return 0;
} 

bool SemanticAnalyzer::print_check_in_var_ref(u_int32_t line,u_int32_t col,std::string var_name){
    if(array_dimention.size() < is_arr){
        fprintf(stderr,"<Error> Found in line %u, column %u: expression of print statement must be scalar type\n",line,col);
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
    }
    return 0;
}

bool SemanticAnalyzer::read_check_in_var_ref(u_int32_t line,u_int32_t col,std::string var_name){
    //fprintf(stderr,"check var array dimention:%lu",array_dimention.size());
    if(array_dimention.size() < is_arr){
        fprintf(stderr,"<Error> Found in line %u, column %u: variable reference of read statement must be scalar type\n",line,col);
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
    }
    return 0;
}

bool SemanticAnalyzer::array_dim_over_def(u_int32_t line,u_int32_t col,std::string var_name){
    if(array_dimention.size() > is_arr){
        //if(this->unary_using)unary_error = 1;
        fprintf(stderr,"<Error> Found in line %u, column %u: there is an over array subscript on '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    return 0;
}

bool SemanticAnalyzer::function_ref(FunctionInvocationNode &var_node){
    std::string var_name = var_node.getNameCString();
    int line = var_node.getLocation().line;
    int col = var_node.getLocation().col;

    int global_undefined = 1; // did not define
    int global_nonvariable = 1; // is function
    int global_not_valid_var = 0; // not valid variable
    int global_is_function = 0;

    int read_const_loopvar = 0; // read node, const or loop variable
    
    for(unsigned int i = 0;i < global_table->entries.size();i++){
        //fprintf(stderr,"check:%s, cur table entry:%s, cur table entry kind:%s\n",var_name.c_str(),global_table->entries[i].name.c_str(),global_table->entries[i].kind.c_str());
        if (global_table->entries[i].name == var_name) {
            if(global_table->entries[i].not_valid_entry){
                global_not_valid_var = 1;
                continue;
            }
            global_not_valid_var = 0;
            global_undefined = 0;
            if(global_table->entries[i].kind == "function"){
                global_is_function = 1;
                // fprintf(stderr,"global table size:%lu\n",global_table->entries[i].parameter_.size());
                for(unsigned int j = 0;j < global_table->entries[i].parameter_.size();j++){
                    std::string tmp = global_table->entries[i].parameter_[j];
                    //fprintf(stderr,"global table size:%s\n",tmp.c_str());
                    func_parameter.push_back(tmp);
                }
                // fprintf(stderr,"check fun_parameter size:%lu\n",func_parameter.size());
                break;
            }
            // fprintf(stderr,"check:%s, \n",cur_table->entries[i].ptype->getPTypeCString())
            break;
        }
    }
    //fprintf(stderr,"function name:%s,function unvocation:%d\n",var_name.c_str(),this->func_invocation_using);
    
    int undefined = 1; // did not define
    int nonvariable = 1; // is function
    int not_valid_var = 0; // not valid variable
    int arr_dimension = 0;
    int is_function = 0;
    cur_table = manager.tables.top();
    for(unsigned int i = 0;i < cur_table->entries.size();i++){
        // fprintf(stderr,"check:%s, cur table entry:%s, cur table entry kind:%s\n",var_name.c_str(),cur_table->entries[i].name.c_str(),cur_table->entries[i].kind.c_str());
        if (cur_table->entries[i].name == var_name) {
            if(cur_table->entries[i].not_valid_entry){
                not_valid_var = 1;
                continue;
            }
            not_valid_var = 0;
            undefined = 0;
            if(cur_table->entries[i].kind == "variable" || cur_table->entries[i].kind == "loop_var" || cur_table->entries[i].kind == "constant"){
                nonvariable = 0;
                if(this->read_using && (cur_table->entries[i].kind == "loop_var" || cur_table->entries[i].kind == "constant"))read_const_loopvar = 1;
                //break;
            }
            else if(cur_table->entries[i].kind == "function"){
                is_function = 1;
                // fprintf(stderr,"curtable size:%lu\n",cur_table->entries[i].parameter_.size());
                for(unsigned int j = 0;j < cur_table->entries[i].parameter_.size();j++){
                    func_parameter.push_back(cur_table->entries[i].parameter_[j]);
                }
                break;
            }
            // fprintf(stderr,"check:%s, \n",cur_table->entries[i].ptype->getPTypeCString());

            if(cur_table->entries[i].ptype->m_dimensions.size() > 0 ){
                arr_dimension = cur_table->entries[i].ptype->m_dimensions.size();
                array_ptype_ptr = cur_table->entries[i].ptype;
            }
            else{
                arr_dimension = 0;
            }
            break;
        }
    }

    if(not_valid_var || global_not_valid_var) {
        // fprintf(stderr,"inside not valid var\n");
        return 1;
    }
    if(cur_table->func_name == var_name){
        undefined = 0;
    }

    if(is_function || global_is_function)return 0;

    if((undefined == 1 && !not_valid_var) && (global_undefined == 1 && !global_not_valid_var)){
        fprintf(stderr,"<Error> Found in line %u, column %u: use of undeclared symbol '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    if(is_function == 0 && !not_valid_var && global_is_function == 0 && !global_not_valid_var){
        fprintf(stderr,"<Error> Found in line %u, column %u: call of non-function symbol '%s'\n",line,col,var_name.c_str());
        fprintf(stderr,"    %s\n",this->src[line]);
        fprintf(stderr,"    %*c\n",col,'^');
        this->sematic_error = 1;
        return 1;
    }
    return 0;
}