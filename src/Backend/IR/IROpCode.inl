
#if !defined( EMIT_IR_INS)
#define EMIT_IR_INS(x, name, haveRet,...)
#endif /// !defined( EMIT_IR_INS)

#define DEFINE_IR_RANGE_BEG(x,name,...) 
#define DEFINE_IR_RANGE_END(x,name,...) 
#define DEFINE_ARITHMETIC_IR_RANGE_BEG(x,name,...)
#define DEFINE_ARITHMETIC_IR_RANGE_END(x,name,...)

#define FIRST_CONTROL_IR_INS(x,name)         DEFINE_IR_RANGE_BEG(x,name)
#define LAST_CONTROL_IR_INS(x,name)          DEFINE_IR_RANGE_END(x,name)

#define FIRST_EMIT_IR_INS(x,name)			 DEFINE_IR_RANGE_BEG(x,name)
#define LAST_EMIT_IR_INS(x,name)             DEFINE_IR_RANGE_END(x,name)

#define FIRST_MEMORY_IR_INS(x,name)          DEFINE_IR_RANGE_BEG(x,name)
#define LAST_MEMORY_IR_INS(x,name)           DEFINE_IR_RANGE_END(x,name)

#define FIRST_CAST_IR_INS(x,name)            DEFINE_IR_RANGE_BEG(x,name)
#define LAST_CAST_IR_INS(x,name)             DEFINE_IR_RANGE_END(x,name)

#define FIRST_PSEUDO_IR_INS(x,name)          DEFINE_IR_RANGE_BEG(x,name)
#define LAST_PSEUDO_IR_INS(x,name)           DEFINE_IR_RANGE_END(x,name)

#define FIRST_UNARY_IR_INS( x,name)          DEFINE_ARITHMETIC_IR_RANGE_BEG(x,name)
#define LAST_UNARY_IR_INS( x,name)           DEFINE_ARITHMETIC_IR_RANGE_END(x,name)

#define FIRST_BINARY_IR_INS( x,name )        DEFINE_ARITHMETIC_IR_RANGE_BEG(x,name)
#define LAST_BINARY_IR_INS( x,name )         DEFINE_ARITHMETIC_IR_RANGE_END(x,name)


//// enum IR
#ifdef ENUM_IR_INSTRUCTION 
#undef  EMIT_IR_INS
#define EMIT_IR_INS(x,name, haveRet, ... ) k##name = x,
#endif /// ENUM_IR_INSTRUCTION

///
#ifdef RANGE_IR_INSTRUCTION
#undef DEFINE_IR_RANGE_BEG
#undef DEFINE_IR_RANGE_END
#define DEFINE_IR_RANGE_BEG(x,name,...) const static uint32_t  name = x;
#define DEFINE_IR_RANGE_END(x,name,...) const static uint32_t  name = x;
#endif //// RANGE_IR_INSTRUCTION


#ifdef RANGE_ARITHMETIC_IR_INSTRUCTION
#undef DEFINE_ARITHMETIC_IR_RANGE_BEG
#undef DEFINE_ARITHMETIC_IR_RANGE_END
#define DEFINE_ARITHMETIC_IR_RANGE_BEG(x,name,...) const static uint32_t name = x;
#define DEFINE_ARITHMETIC_IR_RANGE_END(x,name,...) const static uint32_t name = x;
#endif //// RANGE_ARITHMETIC_IR_INSTRUCTION


#ifdef IR_INSTRUCTION_TO_STR
#undef EMIT_IR_INS
#define EMIT_IR_INS(x,name, ...) case Instruction::OpCode::k##name:return #name;break;
#endif //// IR_INSTRUCTION_TO_STR

FIRST_CONTROL_IR_INS(0,ControlIRInsBeg )
EMIT_IR_INS( 0, Jmp,               false )
EMIT_IR_INS( 1, Br,                false )
EMIT_IR_INS( 3, Call,              false )
EMIT_IR_INS( 4, Ret,               false )
LAST_CONTROL_IR_INS( 4,ControlIRInsEnd )

FIRST_EMIT_IR_INS( 5,ArithmeticIRInsBeg )
FIRST_UNARY_IR_INS( 5, UnaryIRInsBeg )
EMIT_IR_INS( 5,   Sin,            true,           UNARY)
EMIT_IR_INS( 6,   Cos,            true,           UNARY)
EMIT_IR_INS( 7,   Tan,            true,           UNARY)
EMIT_IR_INS( 8,   Exp,            true,           UNARY)
EMIT_IR_INS( 9,   Log,            true,           UNARY)
EMIT_IR_INS( 10,  Not,            true,           UNARY)
EMIT_IR_INS( 11,  T,              true,           UNARY)
EMIT_IR_INS( 12,  Invert,         true,           UNARY)
EMIT_IR_INS( 13,  BitNegate,      true,           UNARY )
LAST_UNARY_IR_INS( 13, UnaryIRInsEnd )

FIRST_BINARY_IR_INS(14, BinaryIRInsBeg)
EMIT_IR_INS( 14, Add,             true,           BINARY )
EMIT_IR_INS( 15, Minus,           true,           BINARY )
EMIT_IR_INS( 16, Mul,             true,           BINARY )
EMIT_IR_INS( 17, Div,             true,           BINARY )
EMIT_IR_INS( 18, Mod,             true,           BINARY )

EMIT_IR_INS( 19, DotAdd,          true,           BINARY )
EMIT_IR_INS( 20, DotMinus,        true,           BINARY )
EMIT_IR_INS( 21, DotMul,          true,           BINARY )
EMIT_IR_INS( 22, DotDiv,          true,           BINARY )
EMIT_IR_INS( 23, DotMod,          true,           BINARY )

/// for bool datatype 
EMIT_IR_INS( 24, And,             true,           BINARY )
EMIT_IR_INS( 25, Or,              true,           BINARY )
EMIT_IR_INS( 26, Xor,             true,           BINARY )
/// for bit datatpye
EMIT_IR_INS( 27, BitAnd,          true,           BINARY )
EMIT_IR_INS( 28, BitOr,           true,           BINARY )
EMIT_IR_INS( 29, BitXor,          true,           BINARY )

EMIT_IR_INS( 30, Dot,             true,           BINARY )
EMIT_IR_INS( 31, Length2,         true,           BINARY )
EMIT_IR_INS( 32, Cross,           true,           BINARY )

EMIT_IR_INS( 33, Equal,           true,           BINARY )
EMIT_IR_INS( 34, NotEqual,        true,           BINARY )
EMIT_IR_INS( 35, Less,            true,           BINARY )
EMIT_IR_INS( 36, LessEqual,       true,           BINARY )
EMIT_IR_INS( 37, Greater,         true,           BINARY )
EMIT_IR_INS( 38, GreaterEqual,    true,           BINARY )
LAST_BINARY_IR_INS(38, BinaryIRInsEnd )
LAST_EMIT_IR_INS(38, ArithmeticIRInsEnd )


FIRST_MEMORY_IR_INS( 39, MemoryIRInsBeg )
EMIT_IR_INS( 39, Alloc,          true )
EMIT_IR_INS( 40, Assign,         true )
LAST_MEMORY_IR_INS(40, MemoryIRInsEnd)


FIRST_CAST_IR_INS(41, CastIRInsBeg)
EMIT_IR_INS(41, Cast,            true )
LAST_CAST_IR_INS(41, CastIRInsEnd)


FIRST_PSEUDO_IR_INS( 42, PseudoIRInsBeg)
EMIT_IR_INS( 42, Label,          false)
EMIT_IR_INS( 43, Error,          true )
EMIT_IR_INS( 44, Phi,            true)
LAST_PSEUDO_IR_INS(44, PseudoIRInsEnd )

#undef EMIT_IR_INS
#undef DEFINE_IR_RANGE_BEG
#undef DEFINE_IR_RANGE_END
#undef DEFINE_ARITHMETIC_IR_RANGE_BEG
#undef DEFINE_ARITHMETIC_IR_RANGE_END

#undef FIRST_CONTROL_IR_INS
#undef LAST_CONTROL_IR_INS

#undef FIRST_EMIT_IR_INS
#undef LAST_EMIT_IR_INS

#undef FIRST_MEMORY_IR_INS
#undef LAST_MEMORY_IR_INS

#undef FIRST_CAST_IR_INS
#undef LAST_CAST_IR_INS

#undef FIRST_PSEUDO_IR_INS
#undef LAST_PSEUDO_IR_INS

#undef FIRST_UNARY_IR_INS
#undef LAST_UNARY_IR_INS

#undef FIRST_BINARY_IR_INS
#undef LAST_BINARY_IR_INS




