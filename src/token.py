import re
from dataclasses import dataclass


def _word_regex(word):
    return rf'\b{re.escape(word)}\b'


def _sanitize_token_name(word):
    return word.upper().replace('.', '_')

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

shared_keyword_words = [
    'format', 'win_32', 'win_64', 'elf_32', 'elf_64', 'bin', 'efi_32', 'efi_64',
    'arch', 'x86_16', 'x86_32', 'x86_64', 'entry', 'declare',
    'db', 'dw', 'dd', 'dq', 'rb', 'rw', 'rd', 'rq', 'int8', 'int16', 'int32', 'int64',
    'uint8', 'uint16', 'uint32', 'float', 'double', 'char',
    'struct', 'ends', 'macro', 'endm', 'if', 'else', 'switch', 'case', 'while', 'do',
    'for', 'input',
    'mov', 'add', 'sub', 'mul', 'div', 'sqr', 'pow', 'cmp', 'jmp', 'jnz', 'inc', 'dec',
    'xor', 'and', 'or', 'not', 'shl', 'shr', 'sar', 'rol', 'ror', 'ret', 'int', 'syscall',
    'ldr', 'str', 'orr', 'eor', 'bic', 'lsl', 'lsr', 'asr', 'tst', 'b', 'bl_op', 'bx_op',
    'adr', 'sdiv', 'udiv', 'bfi', 'ubfx', 'cbz', 'cbnz', 'lui', 'auipc', 'lw', 'sw', 'ld',
    'sd', 'addi', 'slt', 'slti', 'jal', 'jalr', 'li', 'la', 'ecall', 'beq', 'bne', 'blt',
    'bge', 'out', 'in', 'cli', 'sti', 'lidt', 'lgdt', 'smsw', 'lmsw', 'invlpg', 'wbinvd',
    'rdmsr', 'wrmsr', 'rdtsr', 'cpuid', 'iret', 'pushfd', 'popfd', 'lahf', 'sahf', 'stall',
    'reset', 'allocate_pages', 'free_pages', 'get_memory_map', 'allocate_pool', 'free_pool',
    'set_watchdog_timer', 'connect_controller', 'disconnect_controller', 'open_protocol',
    'locate_handle', 'locate_device_path', 'install_protocol_interface',
    'reinstall_protocol_interface', 'uninstall_protocol_interface', 'handle_protocol',
    'register_protocol_notify', 'locate_handle_buffer', 'print', 'call', 'import',
    'export', 'return', 'break', 'continue',
    'push', 'pop', 'lea', 'nop', 'xchg', 'xadd', 'bsf', 'bsr', 'bt', 'bts', 'btr', 'btc',
    'test', 'cmovz', 'cmovnz', 'cmova', 'cmovae', 'cmovb', 'cmovbe', 'cmovg', 'cmovge',
    'cmovl', 'cmovle', 'leave', 'enter', 'hlt', 'cld', 'std', 'stc', 'clc', 'cmc', 'rep',
    'repe', 'repne', 'stos', 'lods', 'movs', 'scas', 'cmps', 'imul', 'idiv', 'neg', 'adc',
    'sbb', 'fld', 'fst', 'fstp', 'fadd', 'fsub', 'fmul', 'fdiv', 'fsqrt', 'fabs', 'fchs',
    'fcom', 'movd', 'movq', 'movaps', 'movups', 'addps', 'subps', 'mulps', 'divps',
    'sqrtps', 'addpd', 'subpd', 'mulpd', 'divpd', 'sqrtpd', 'andps', 'orps', 'xorps',
    'vaddps', 'vsubps', 'vmulps', 'vdivps', 'vxorps', 'vandps', 'vorps', 'jz', 'je', 'jne',
    'ja', 'jae', 'jb', 'jbe', 'jg', 'jge', 'jl', 'jle', 'jo', 'jno', 'js', 'jns',
    'adds', 'subs', 'negs', 'adcs', 'sbc', 'sbcs', 'madd', 'msub', 'smull', 'umull',
    'smaddl', 'umaddl', 'ands', 'bics', 'mvn', 'ldrb', 'ldrh', 'ldrsw', 'ldp', 'stp',
    'strb', 'strh', 'bl', 'blr', 'br', 'tbz', 'tbnz', 'cmn', 'svc', 'hvc', 'smc', 'eret',
    'isb', 'dsb', 'dmb', 'msr', 'mrs', 'fcmp', 'fneg', 'fmov', 'sll', 'sltu', 'srl', 'sra',
    'sltiu', 'xori', 'ori', 'andi', 'slli', 'srli', 'srai', 'lb', 'lh', 'lbu', 'lhu', 'sb',
    'sh', 'bltu', 'bgeu', 'mulh', 'mulhsu', 'mulhu', 'divu', 'rem', 'remu', 'lr_w', 'sc_w',
    'amoswap_w', 'amoadd_w', 'amoxor_w', 'amoand_w', 'amoor_w', 'amomin_w', 'amomax_w',
    'amominu_w', 'amomaxu_w', 'csrrw', 'csrrs', 'csrrc', 'csrrwi', 'csrrsi', 'csrrci',
    'ebreak', 'c.add', 'c.addi', 'c.li', 'c.lui', 'c.mv', 'c.j', 'c.jal', 'c.beqz',
    'c.bnez', 'c.lw', 'c.sw', 'c.srli', 'c.srai', 'c.andi', 'c.sub', 'c.xor', 'c.or',
    'c.and'
]

x86_register_words = [
    'rax', 'rbx', 'rcx', 'rdx', 'rsp', 'rbp', 'rsi', 'rdi',
    'r8', 'r9', 'r10', 'r11', 'r12', 'r13', 'r14', 'r15',
    'eax', 'ebx', 'ecx', 'edx', 'esp', 'ebp', 'esi', 'edi',
    'r8d', 'r9d', 'r10d', 'r11d', 'r12d', 'r13d', 'r14d', 'r15d',
    'ax', 'bx', 'cx', 'dx', 'sp', 'bp', 'si', 'di',
    'r8w', 'r9w', 'r10w', 'r11w', 'r12w', 'r13w', 'r14w', 'r15w',
    'al', 'bl', 'cl', 'dl', 'ah', 'bh', 'ch', 'dh',
    'spl', 'bpl', 'sil', 'dil',
    'r8b', 'r9b', 'r10b', 'r11b', 'r12b', 'r13b', 'r14b', 'r15b',
    'cs', 'ds', 'es', 'fs', 'gs', 'ss',
    'rip', 'eip', 'ip', 'rflags', 'eflags', 'flags'
]

arm_register_words = [
    *[f'x{index}' for index in range(31)],
    *[f'w{index}' for index in range(31)]
]

riscv_register_words = [
    'x31',
    'zero', 'ra', 'sp', 'gp', 'tp', 't0', 't1', 't2', 's0', 'fp', 's1',
    'a0', 'a1', 'a2', 'a3', 'a4', 'a5', 'a6', 'a7',
    's2', 's3', 's4', 's5', 's6', 's7', 's8', 's9', 's10', 's11',
    't3', 't4', 't5', 't6',
    *[f'f{index}' for index in range(32)],
    *[f'd{index}' for index in range(32)],
    'ft0', 'ft1', 'ft2', 'ft3', 'ft4', 'ft5', 'ft6', 'ft7',
    'fs0', 'fs1', 'fa0', 'fa1', 'fa2', 'fa3', 'fa4', 'fa5', 'fa6', 'fa7',
    'fs2', 'fs3', 'fs4', 'fs5', 'fs6', 'fs7', 'fs8', 'fs9', 'fs10', 'fs11',
    'ft8', 'ft9', 'ft10', 'ft11',
    'pc'
]

registers = set(x86_register_words + arm_register_words + riscv_register_words)

reg_pattern = r'\b(' + '|'.join(sorted(registers, key=len, reverse=True)) + r')\b'

token_types_list = {
    #Derectives and formats
    'ARCH': TokenType("ARCH", r'\barch\b'),
    'FORMAT': TokenType("FORMAT", r'\bformat\b'),
    'DECLARE': TokenType("DECLARE", r'\bdeclare\b'),
    'ENTRY': TokenType("ENTRY", r'\bentry\b'),
    'ENDF': TokenType("ENDF", r'\bfunction\b'),
    
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

    'TYPE_FLOAT': TokenType("TYPE_FLOAT", r'\bfloat\b'),
    'TYPE_DOUBLE': TokenType("TYPE_DOUBLE", r'\bdouble\b'),
    'TYPE_CHAR': TokenType("TYPE_CHAR", r'\bchar\b'),
    'TYPE_CHAR_ARRAY': TokenType("TYPE_CHAR_ARRAY", r'\bchar\[\]\b'),
    'TYPE_STRING': TokenType("TYPE_STRING", r'\bstring\b'),

    #ASM instructions
    'MOV': TokenType("MOV", r'\bmov\b'),
    'ADD': TokenType("ADD", r'\badd\b'),
    'SUB': TokenType("SUB", r'\bsub\b'),

    #High level instructions
    'PRINT': TokenType("PRINT", r'\bprint\b'),
    'IF': TokenType("IF", r'\bif\b'),
    'ELSE': TokenType("ELSE", r'\belse\b'),

    #Punctuation
    'ASSIGN': TokenType("ASSIGN", r'='),
    'COLON': TokenType("COLON", r':'),
    'SEMI': TokenType("SEMI", r';'),
    'COMMA': TokenType("COMMA", r','),
    'LBRACE': TokenType("LBRACE", r'\{'),
    'RBRACE': TokenType("RBRACE", r'\}'),
    'LBRACKET': TokenType("LBRACKET", r'\['),
    'RBRACKET': TokenType("RBRACKET", r'\]'),
    'LPARENT': TokenType("LPARENT", r'\('),
    'RPARENT': TokenType("RPARENT", r'\)'),
    'LESS': TokenType("LESS", r'<'),
    'GREATER': TokenType("GREATER", r'>'),
    'DOT': TokenType("DOT", r'\.'),
    'STAR': TokenType("STAR", r'\*'),
    'MODULE': TokenType("MODULE", r'%'),
    'AMPERSAND': TokenType("AMPERSAND", r'&'),
    'PLUS': TokenType("PLUS", r'\+'),
    'MINUS': TokenType("MINUS", r'-'),
    'DIVIDE': TokenType("DIVIDE", r'/'),
    'HASH': TokenType("HASH", r'#'),
    'IS_EQUAL': TokenType("IS_EQUAL", r'=='),
    'NOT_EQUAL': TokenType("NOT_EQUAL", r'!='),
    'LESS_OR_EQUAL': TokenType("LESS_OR_EQUAL", r'<='),
    'GREATER_OR_EQUAL': TokenType("GREATER_OR_EQUAL", r'>='),
    'LOGICAL_AND': TokenType("LOGICAL_AND", r'&&'),
    'LOGICAL_OR': TokenType("LOGICAL_OR", r'\|\|'),
    'INCREMENTAL': TokenType("INCREMENTAL", r'\+\+'),
    'DECREMENTAL': TokenType("DECREMENTAL", r'--'),
    'NUMBER': TokenType("NUMBER", r'\b\d+(?:\.\d+)?\b'),
    'STRING': TokenType("STRING", r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''),
}

for keyword in shared_keyword_words:
    token_name = _sanitize_token_name(keyword)
    token_types_list[token_name] = TokenType(token_name, _word_regex(keyword))
