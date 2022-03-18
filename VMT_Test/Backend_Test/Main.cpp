#include <stdio.h>
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Backend/IR/IRBuilder.h"
#include "Backend/IRWriter/IRWriter.h"
#include "Backend/IR/ValueDAG.h"
#include "Backend/FlowGraphDisplay/DotCodeGen.h"
#include "Backend/FlowGraphDisplay/BasicBlockDotCodeGen.h"
#include "Backend/FlowGraphDisplay/ValueDAGCodeGen.h"
#include "ADT/graphs_algorithm.h"

/// <summary>
/// 我们的目标之一就是要做一个简单,好用的IR
/// </summary>
/// <param name=""></param>
/// <param name=""></param>

TEST(test_ir, test_ir) {

    std::shared_ptr<IR::IRContext> TheContext = std::make_shared<IR::IRContext>( );
    std::shared_ptr<IR::IRBuilder> TheBuilder = std::make_shared<IR::IRBuilder>( TheContext );

    IR::FunctionType *funcType = new IR::FunctionType( TheContext->getTypeManger().getFloatType(4));

    funcType->addParamType( TheContext->getTypeManger().getIntegerType(sizeof(int)));
    funcType->addParamType( TheContext->getTypeManger().getIntegerType(sizeof(int)));
    funcType->addParamType( TheContext->getTypeManger().getIntegerType(sizeof(int)));


    IR::Function* func = TheBuilder->emitFunction("MyFunction", funcType);
    IR::Function* currentFunc = TheContext->getCurrentFunction( );
    auto nameAlloc   = currentFunc->getNameAlloc( );
    std::string name = nameAlloc->allocName("test_Name");
    std::cout << name << std::endl;
    name = nameAlloc->allocName("test_Name");
    std::cout << name << std::endl;
    EXPECT_EQ(func, currentFunc);
    EXPECT_EQ(currentFunc->getFunctionName(), "MyFunction");

    for (size_t i = 0; i < funcType->sizeParamsType( ); ++i ) {
        IR::Type const* type = funcType->atParamType(i);
        std::string name = "p" + std::to_string(i);
        auto p = TheBuilder->emitAlloc( type, name.c_str());
        func->addArgs( p );
    }
    
    IR::Value * value = TheBuilder->emitAlloc(12.123f, "t1");

    EXPECT_EQ(true, value->isConstant());
    IR::Value* tv1 = TheBuilder->emitAlloc( TheContext->getTypeManger().getFloatType(sizeof(float)), "test_name");
    EXPECT_EQ(false, tv1->isConstant());

    std::cout << value->emitStr() << std::endl;


    IR::Value* v2 = TheBuilder->emitAlloc(12.454f,"t2");
    auto ins = v2->getInstruction();
    EXPECT_NE(ins, nullptr);

    IR::Value* addIns = TheBuilder->emitAdd(value, v2, "add");
    EXPECT_NE(addIns, nullptr);
    EXPECT_EQ(false, addIns->isConstant());
    EXPECT_EQ(true,  addIns->isLocal());
    EXPECT_EQ(false, addIns->isStatic());
    EXPECT_EQ(false, addIns->isVolatile());
    ins = addIns->getInstruction();
    EXPECT_NE(ins, nullptr);
    EXPECT_EQ(ins->getOpCode(), IR::Instruction::OpCode::kAdd);
    EXPECT_EQ(ins->isBinaryOp(), true);
    if (true == ins->isBinaryOp()) {
        auto bins = static_cast<IR::BinaryOpIns*>( ins );
        EXPECT_EQ(bins->getFirstOperand(), value);
        EXPECT_EQ(bins->getSecondOperand(), v2);
        IR::Users const& users = value->getUsers();
        EXPECT_EQ(false, users.empty());
        EXPECT_EQ(1, users.size());
        EXPECT_EQ(bins->getRetValue(),*(users.cbegin()));
    }
    EXPECT_EQ(ins->getInsType(), IR::InstructionType::kArithmetic);
    
    IR::Value* MinusIns = TheBuilder->emitMul(addIns, v2, "minus");
    EXPECT_NE(MinusIns, nullptr);
    
    IR::Label* label = TheBuilder->emitLabel("label");
    IR::Label* label1 = TheBuilder->emitLabel("true.cond");
    EXPECT_NE(nullptr, label);
    IR::Br * br = TheBuilder->emitBr(MinusIns, "true.cond","label");
    
    IR::IRWriter writer(TheContext);
    writer.write(func, std::cout );
}


TEST(test_ir, test_basicblock_JmpBlock) {

    std::shared_ptr<IR::IRContext> TheContext = std::make_shared<IR::IRContext>();
    std::shared_ptr<IR::IRBuilder> TheBuilder = std::make_shared<IR::IRBuilder>(TheContext);
    IR::FunctionType* funcType = new IR::FunctionType(TheContext->getTypeManger().getFloatType(4));
    IR::Function* func = TheBuilder->emitFunction("MyFunction", funcType);
    IR::Label* Lsss = TheBuilder->emitLabel("Lsss");
    IR::Label* Lsss1 = TheBuilder->emitLabel("Lsss1");
    IR::Br* br     = TheBuilder->emitBr( nullptr , "LStart", "L1");
    IR::Label* Ls  = TheBuilder->emitLabel("LStart");
    IR::Value* t1  = TheBuilder->emitAlloc(12.123f, "t1");
    IR::Value* t2  = TheBuilder->emitAlloc(12.454f, "t2");
    IR::Value* add = TheBuilder->emitAdd(t1, t2, "add");
    IR::Ret* ret = TheBuilder->emitRet( add );
    IR::Label* L1  = TheBuilder->emitLabel("L1");
    IR::Value* t3  = TheBuilder->emitAlloc(12.34f, "t3");
    IR::Value* add1 = TheBuilder->emitAdd(t2, t3, "add1");
    IR::Br* jmpL1 = TheBuilder->emitBr(nullptr, "LStart", "L1");

    

    auto flowGraph = func->getFlowGraphs();

    dot::adjacency_list_dot_codegen<IR::BasicBlock> dotCodegen( &(flowGraph->graphData()));
    std::string str = dotCodegen.codegen<IR::VertexBasicBlockDotCodeGen, IR::EdgeBasicBlockDotCodeGen>("BasicBlock");
    std::cout << str << std::endl;
}

TEST(test_ir, test_basicblock_valuedag) {
    /// <summary>
    /// 在 IR 这层,是没有什么类,什么模板的,这层最多就是拥有模块,拥有函数这两个概念
    /// </summary>
    /// 
    std::shared_ptr<IR::IRContext> TheContext = std::make_shared<IR::IRContext>();
    std::shared_ptr<IR::IRBuilder> TheBuilder = std::make_shared<IR::IRBuilder>(TheContext);
    IR::FunctionType* funcType = new IR::FunctionType(TheContext->getTypeManger().getFloatType(4));
    
    IR::Function* func = TheBuilder->emitFunction("MyFunction", funcType);

    IR::Value* b = TheBuilder->emitAlloc( TheContext->getTypeManger().getIntegerType(4), "b");
    IR::Value* c = TheBuilder->emitAlloc( TheContext->getTypeManger().getIntegerType(4), "c");
    IR::Value* d = TheBuilder->emitAlloc( TheContext->getTypeManger().getIntegerType(4), "d");
    IR::Value* a = TheBuilder->emitAdd(b, c, "a");

    IR::Value* t1 = TheBuilder->emitMinus(a, d);
    TheBuilder->emitAssign(b, t1);
    IR::Value* t2 = TheBuilder->emitMinus(b, c);
    TheBuilder->emitAssign(c, t2);
    IR::Value* t3 = TheBuilder->emitMinus(a, d );
    TheBuilder->emitAssign(d, t3);

    auto flowGraph = func->getFlowGraphs();
    
    for (auto begin = flowGraph->graphData().begin(); begin != flowGraph->graphData().end(); ++begin) {
        auto ValueDAG = IR::ValueDAG::makeValueDAG(&((*begin)->data()));
        dot::adjacency_list_dot_codegen<IR::ValueDAG::Node> dotCodegen(& ValueDAG->getAdjacency_list());
        std::vector<ADT::graph::vertex<IR::ValueDAG::Node>> start = ADT::graph::get_start_vertex(ValueDAG->getAdjacency_list());
        std::vector<ADT::graph::vertex<IR::ValueDAG::Node>> end = ADT::graph::get_end_vertex(ValueDAG->getAdjacency_list());
        if (start.size() != 0) {
            std::cout << "start vertex = [" << std::endl;
            for (size_t i = 0; i < start.size(); ++i) {
                std::cout << start[i]->data().getValue()->getValueName() << std::endl;
            }
            std::cout << "]" << std::endl;
        }
        if (end.size() != 0) {
            std::cout << "End vertex = [" << std::endl;
            for (size_t i = 0; i < end.size(); ++i) {
                std::cout << end[i]->data().getValue()->getValueName() << std::endl;
            }
            std::cout << "]" << std::endl;
        }
        std::string str = dotCodegen.codegen<IR::VertexValueDAGDotCodeGen, IR::EdgeValueDAGDotCodeGen>("BasicBlock");
        std::cout << str << std::endl;
    }

}


TEST(test_quick_sort, test_basicblock) {
    std::shared_ptr<IR::IRContext> TheContext = std::make_shared<IR::IRContext>();
    std::shared_ptr<IR::IRBuilder> TheBuilder = std::make_shared<IR::IRBuilder>(TheContext);
    IR::FunctionType* funcType = new IR::FunctionType( TheContext->getTypeManger().getFloatType(4));
    IR::Function* func = TheBuilder->emitFunction("MyFunction", funcType);
    IR::Value* vm = TheBuilder->emitAlloc(0.0f, "m");
    TheBuilder->emitAlloc(0.0f, "n");
    
    IR::IntegerConstant* IC_1 = new IR::IntegerConstant(TheContext->getTypeManger().getIntegerType(4), 1);
    TheBuilder->emitAssign( "m", "i");
    
    TheBuilder->emitMinus( vm, IC_1, "i");
    
    TheBuilder->emitAssign("n", "j");



}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS( );
}
