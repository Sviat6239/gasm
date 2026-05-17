from dataclasses import dataclass

@dataclass(frozen=True)
class TokenType:
    name: str
    regex: str

    def __repr__(self):
        return f"TokenType({self.name})"

@dataclass
class Token:
    type: TokenType
    value: str
    position: int
    line: int = 1
    column: int = 1

    def __repr__(self):
        return f"Token({self.type.name}, '{self.value}', at {self.line}:{self.column})"  

x86_registers = {
    'rax', 'rbx', 'rcx', 'rdx', 'rsp', 'rbp', 'rsi', 'rdi',
    'r8', 'r9', 'r10', 'r11', 'r12', 'r13', 'r14', 'r15',
    'eax', 'ebx', 'ecx', 'edx', 'esp', 'ebp', 'esi', 'edi',
    'r8d', 'r9d', 'r10d', 'r11d', 'r12d', 'r13d', 'r14d', 'r15d',
    'ax', 'bx', 'cx', 'dx', 'sp', 'bp', 'si', 'di',
    'r8w', 'r9w', 'r10w', 'r11w', 'r12w', 'r13w', 'r14w', 'r15w',
    'al', 'bl', 'cl', 'dl', 'ah', 'bh', 'ch', 'dh',
    'spl', 'bpl', 'sil', 'dil',
    'r8b', 'r9b', 'r10b', 'r11b', 'r12b', 'r13b', 'r14b', 'r15b',
    'rip', 'rflags'
}

reg_pattern = r'\b(' + '|'.join(sorted(x86_registers, key=len, reverse=True)) + r')\b'

token_types_list = {
    #Derectives and formats
    'ARCH': TokenType("ARCH", r'\barch\b'),
    'FORMAT': TokenType("FORMAT", r'\bformat\b'),
    'DECLARE': TokenType("DECLARE", r'\bdeclare\b'),
    'ENTRY': TokenType("ENTRY", r'\bentry\b'),
    
    #Registers 
    'REGISTER': TokenType("REGISTER", reg_pattern),

    #Data types
    'TYPE_DB': TokenType("TYPE_DB", r'\bdb\b'),
    'TYPE_DW': TokenType("TYPE_DW", r'\bdw\b'),
    'TYPE_DD': TokenType("TYPE_DD", r'\bdd\b'),
    'TYPE_DQ': TokenType("TYPE_DQ", r'\bdq\b'),

    'TYPE_RB': TokenType("TYPE_RB", r'\brb\b'),
    'TYPE_RW': TokenType("TYPE_RW", r'\brw\b'),
    'TYPE_RD': TokenType("TYPE_RD", r'\brd\b'),
    'TYPE_RQ': TokenType("TYPE_RQ", r'\brq\b'),

    'TYPE_INT8': TokenType("TYPE_INT8", r'\bint8\b'),
    'TYPE_INT16': TokenType("TYPE_INT16", r'\bint16\b'),
    'TYPE_INT32': TokenType("TYPE_INT32", r'\bint32\b'),
    'TYPE_INT64': TokenType("TYPE_INT64", r'\bint64\b'),

    'TYPE_UINT8': TokenType("TYPE_UINT8", r'\buint8\b'),
    'TYPE_UINT16': TokenType("TYPE_UINT16", r'\buint16\b'),
    'TYPE_UINT32': TokenType("TYPE_UINT32", r'\buint32\b'),
    'TYPE_UINT64': TokenType("TYPE_UINT64", r'\buint64\b'),

    'TYPE_CHAR_ARRAY': TokenType("TYPE_CHAR_ARRAY", r'\bchar\[\]\b'),
    'TYPE_STRING': TokenType("TYPE_STRING", r'\bstring\b'),

    #ASM instructions
    
}              