#! perl
# usage: perl do-parse.perl <idl-file> [options]

system "parse idl-parser.btab @ARGV -ceol -case";
