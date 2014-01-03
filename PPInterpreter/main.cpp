#include <iostream>
#include <fstream>
#include <iterator>
#include "lexer.h"
#include "ast.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::istream_iterator;

int main(int args, char const *argv[])
{
    if (args < 2){
        cout << "Usage: " << argv[0] << " <SOURCE_FILE_NAME>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    if(!in.good()){
        cout << "File " << argv[1] << " does not exist" << endl;
        in.close();
        return 2;
    }
    in >> std::noskipws;
    Lexer lexer(in);
    Token t = lexer.nextToken();
    while(t.type != Token::Eof){
        cout << t.type << " - " << lexer.getLineNumber() << endl;
        t = lexer.nextToken();
    }
    return 0;
}
