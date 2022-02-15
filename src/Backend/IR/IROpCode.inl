
#if !defined( EMIT_IR_INS)
#define EMIT_IR_INS(x, name,...)
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
#define EMIT_IR_INS(x,name, ... ) k##name = x,
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
EMIT_IR_INS( 0, Jmp )
EMIT_IR_INS( 1, Br  )
EMIT_IR_INS( 3, Call)
EMIT_IR_INS( 4, Ret )
LAST_CONTROL_IR_INS( 4,ControlIRInsEnd )

FIRST_EMIT_IR_INS( 5,ArithmeticIRInsBeg )
FIRST_UNARY_IR_INS( 5, UnaryIRInsBeg )
EMIT_IR_INS( 5,   Sin,            UNARY)
EMIT_IR_INS( 6,   Cos,            UNARY)
EMIT_IR_INS( 7,   Tan,            UNARY)
EMIT_IR_INS( 8,   Exp,            UNARY)
EMIT_IR_INS( 9,   Log,            UNARY)
EMIT_IR_INS( 10,  Not,            UNARY)
EMIT_IR_INS( 11,  T,              UNARY)
EMIT_IR_INS( 12,  Invert,         UNARY)
EMIT_IR_INS( 13,  BitNegate,      UNARY )
LAST_UNARY_IR_INS( 13, UnaryIRInsEnd )

FIRST_BINARY_IR_INS(14, BinaryIRInsBeg)
EMIT_IR_INS( 14, Add,             BINARY )
EMIT_IR_INS( 15, Minus,           BINARY )
EMIT_IR_INS( 16, Mul,             BINARY )
EMIT_IR_INS( 17, Div,             BINARY )
EMIT_IR_INS( 18, Mod,             BINARY )

EMIT_IR_INS( 19, DotAdd,          BINARY )
EMIT_IR_INS( 20, DotMinus,        BINARY )
EMIT_IR_INS( 21, DotMul,          BINARY )
EMIT_IR_INS( 22, DotDiv,          BINARY )
EMIT_IR_INS( 23, DotMod,          BINARY )

/// for bool datatype 
EMIT_IR_INS( 24, And,             BINARY )
EMIT_IR_INS( 25, Or,              BINARY )
EMIT_IR_INS( 26, Xor,             BINARY )
/// for bit datatpye
EMIT_IR_INS( 27, BitAnd,          BINARY )
EMIT_IR_INS( 28, BitOr,           BINARY )
EMIT_IR_INS( 29, BitXor,          BINARY )

EMIT_IR_INS( 30, Dot,             BINARY )
EMIT_IR_INS( 31, Length2,         BINARY )
EMIT_IR_INS( 32, Cross,           BINARY )
LAST_BINARY_IR_INS(32, BinaryIRInsEnd )
LAST_EMIT_IR_INS(32, ArithmeticIRInsEnd )


FIRST_MEMORY_IR_INS( 33, MemoryIRInsBeg )
EMIT_IR_INS( 33, Alloc )
EMIT_IR_INS( 34, Assign  )
LAST_MEMORY_IR_INS(34, MemoryIRInsEnd)


FIRST_CAST_IR_INS(35, CastIRInsBeg)
EMIT_IR_INS(35, Cast)
LAST_CAST_IR_INS(35, CastIRInsEnd)


FIRST_PSEUDO_IR_INS( 36, PseudoIRInsBeg)
EMIT_IR_INS( 36, Label)
EMIT_IR_INS( 37, Error)
EMIT_IR_INS( 38, Indicate)
LAST_PSEUDO_IR_INS(38, PseudoIRInsEnd )

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




