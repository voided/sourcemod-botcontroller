import sys

try:
    from ambuild2 import run
except ImportError:
    sys.exit('Install AMBuild 2.2 or newer from https://github.com/alliedmodders/ambuild.')

parser = run.BuildParser(sourcePath=sys.path[0], api='2.2')
parser.options.add_argument('--sm-path', required=True, help='Path to SourceMod')
parser.options.add_argument('--mms-path', required=True, help='Path to Metamod:Source')
parser.options.add_argument('--hl2sdk-root', required=True, help='Directory containing HL2SDK checkouts')
parser.options.add_argument('--sdks', default='all', help='Space-delimited SDK names, all, or present')
parser.options.add_argument('--targets', default='x86,x86_64', help='Comma-delimited target architectures')
parser.options.add_argument('--enable-optimize', action='store_true', help='Enable optimization')
parser.Configure()
