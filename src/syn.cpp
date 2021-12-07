#include "../include/syn.hpp"
#include "../include/token.hpp"
#include "../include/compilerException.hpp"
#include <map>

using namespace std;
Syn::Syn()
{
  ll1_stack.push(Symbol(TokenType::$, SymbolType::TERMINAL));
  ll1_stack.push(Symbol(ProductionType::EXP, SymbolType::NON_TERMINAL));
  // EXP parser row
  parserTable[ProductionType::EXP][TokenType::TK_LOG] =
  parserTable[ProductionType::EXP][TokenType::TK_ABS] =
  parserTable[ProductionType::EXP][TokenType::TK_SQRT] =
  parserTable[ProductionType::EXP][TokenType::TK_TAN] =
  parserTable[ProductionType::EXP][TokenType::TK_ROUND] =   
  parserTable[ProductionType::EXP][TokenType::TK_COS] =
  parserTable[ProductionType::EXP][TokenType::TK_SIN] = 
  parserTable[ProductionType::EXP][TokenType::TK_E] = 
  parserTable[ProductionType::EXP][TokenType::TK_PI] =
  parserTable[ProductionType::EXP][TokenType::TK_NUMBER] = 1; //EXP → NUM TERM
  parserTable[ProductionType::EXP][TokenType::TK_BEG_DELIMITER] = 2; //EXP → ( EXP ) TERM
  parserTable[ProductionType::EXP][TokenType::TK_OPERATOR_L1] = 3; //EXP →  l1o EXP

  //TERM parser row
  parserTable[ProductionType::TERM][TokenType::TK_END_DELIMITER] =
  parserTable[ProductionType::TERM][TokenType::$] =
  parserTable[ProductionType::TERM][TokenType::TK_SEPARATOR] = -1; //TERM → NULL
  parserTable[ProductionType::TERM][TokenType::TK_OPERATOR_L1] = 
  parserTable[ProductionType::TERM][TokenType::TK_OPERATOR_L2] =
  parserTable[ProductionType::TERM][TokenType::TK_OPERATOR_L3] = 4; //TERM → OPER1 EXP 

  //OPER1 parser row 
  parserTable[ProductionType::OPER1][TokenType::TK_OPERATOR_L1] = 5; //OPER1 → l1o
  parserTable[ProductionType::OPER1][TokenType::TK_OPERATOR_L2] =
  parserTable[ProductionType::OPER1][TokenType::TK_OPERATOR_L3] = 6; //OPER1 → OPER2

  //OPER2 parser row 
  parserTable[ProductionType::OPER2][TokenType::TK_OPERATOR_L2] = 7; //OPER2 → l2o
  parserTable[ProductionType::OPER2][TokenType::TK_OPERATOR_L3] = 8; //OPER2 → OPER3

  //OPER3 parser row 
  parserTable[ProductionType::OPER3][TokenType::TK_OPERATOR_L3] = 9; //OPER3 → l3o

  //NUM parser row 
  parserTable[ProductionType::NUM][TokenType::TK_LOG] =
  parserTable[ProductionType::NUM][TokenType::TK_ABS] =
  parserTable[ProductionType::NUM][TokenType::TK_SQRT] =
  parserTable[ProductionType::NUM][TokenType::TK_TAN] =
  parserTable[ProductionType::NUM][TokenType::TK_SIN] =
  parserTable[ProductionType::NUM][TokenType::TK_ROUND] =
  parserTable[ProductionType::NUM][TokenType::TK_COS] = 10; //NUM → FUNC 
  parserTable[ProductionType::NUM][TokenType::TK_E] = 11; //NUM → e
  parserTable[ProductionType::NUM][TokenType::TK_PI] = 12; //NUM → pi
  parserTable[ProductionType::NUM][TokenType::TK_NUMBER] = 13; //NUM → number
  


  //FUNC parser row 
  parserTable[ProductionType::FUNC][TokenType::TK_LOG] = 14; // FUNC → FUNC2 <(> EXP <,> EXP <)>
  parserTable[ProductionType::FUNC][TokenType::TK_ABS] = 
  parserTable[ProductionType::FUNC][TokenType::TK_SQRT] = 
  parserTable[ProductionType::FUNC][TokenType::TK_TAN] = 
  parserTable[ProductionType::FUNC][TokenType::TK_ROUND] = 
  parserTable[ProductionType::FUNC][TokenType::TK_SIN] =  
  parserTable[ProductionType::FUNC][TokenType::TK_COS] = 15; // FUNC → FUNC1 <(> EXP <)>

  //FUNC1 parser row 
  parserTable[ProductionType::FUNC1][TokenType::TK_ABS] = 16; //FUNC1 → abs
  parserTable[ProductionType::FUNC1][TokenType::TK_SQRT] = 17; //FUNC1 →sqrt
  parserTable[ProductionType::FUNC1][TokenType::TK_TAN] = 18; //FUNC1 → tan
  parserTable[ProductionType::FUNC1][TokenType::TK_SIN] = 19; //FUNC1 → sin
  parserTable[ProductionType::FUNC1][TokenType::TK_ROUND] = 20; //FUNC1 → round
  parserTable[ProductionType::FUNC1][TokenType::TK_COS] = 21; //FUNC1 → cos

  //FUNC2 parser row 
  parserTable[ProductionType::FUNC2][TokenType::TK_LOG] = 22; // FUNC2 → log
  
  
}
Syn::Syn(const string &tkn_filename) : Syn()
{
  tkn_handler = TknHandler(tkn_filename);
}

Syn::~Syn()
{

}
void Syn::parser()
{
  int count = 0;
  Token *tkn = getNextToken();

  while(ll1_stack.size() && tkn != NULL){

    const Symbol top = ll1_stack.top();
    if(top.type == SymbolType::TERMINAL ) {
      ll1_stack.pop();
      
      if(top.symbol == tkn->getType()){
        count++;
        tkn = getNextToken();
      }
      
    } else if(top.type == SymbolType::NON_TERMINAL) {
      ll1_stack.pop();
      int production = parserTable[ProductionType(top.symbol)][tkn->getType()];
 
      switch (production)
      {
        case -1: //TERM → NULL
        // ll1_stack.pop();
        break;
        
        case 1: //EXP → NUM TERM
        ll1_stack.push(Symbol(ProductionType::TERM, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(ProductionType::NUM, SymbolType::NON_TERMINAL));
        break;
        
        case 2: //EXP → ( EXP ) TERM
        ll1_stack.push(Symbol(ProductionType::TERM, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(TokenType::TK_END_DELIMITER, SymbolType::TERMINAL));
        ll1_stack.push(Symbol(ProductionType::EXP, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(TokenType::TK_BEG_DELIMITER, SymbolType::TERMINAL));
        break;
        
        case 3: //EXP →  l1o EXP
        ll1_stack.push(Symbol(ProductionType::EXP, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(TokenType::TK_OPERATOR_L1, SymbolType::TERMINAL));
        break;
        
        case 4: //TERM → OPER1 EXP
        ll1_stack.push(Symbol(ProductionType::EXP, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(ProductionType::OPER1, SymbolType::NON_TERMINAL));
        break;
        
        case 5: //OPER1 → l1o
        ll1_stack.push(Symbol(TokenType::TK_OPERATOR_L1, SymbolType::TERMINAL));
        break;
        
        case 6: //OPER1 → OPER2
        ll1_stack.push(Symbol(ProductionType::OPER2, SymbolType::NON_TERMINAL));
       
        break;
        
        case 7: //OPER2 → l2o
        ll1_stack.push(Symbol(TokenType::TK_OPERATOR_L2, SymbolType::TERMINAL));
       
        break;

        case 8: //OPER2 → OPER3
        ll1_stack.push(Symbol(ProductionType::OPER3, SymbolType::NON_TERMINAL));
        break;
        
        case 9: //OPER3 → l3o
        ll1_stack.push(Symbol(TokenType::TK_OPERATOR_L3, SymbolType::TERMINAL));
        break;

        case 10: //NUM → FUNC 
        ll1_stack.push(Symbol(ProductionType::FUNC, SymbolType::NON_TERMINAL));
        break;
        
        case 11: //NUM → e
        ll1_stack.push(Symbol(TokenType::TK_E, SymbolType::TERMINAL));
        break;

        case 12: //NUM → pi
         ll1_stack.push(Symbol(TokenType::TK_PI, SymbolType::TERMINAL));
        break;
        
        case 13: //NUM → number
        ll1_stack.push(Symbol(TokenType::TK_NUMBER, SymbolType::TERMINAL));
        break;

        case 14: //FUNC → FUNC2 <(> EXP <,> EXP <)>
        ll1_stack.push(Symbol(TokenType::TK_END_DELIMITER, SymbolType::TERMINAL));
        ll1_stack.push(Symbol(ProductionType::EXP, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(TokenType::TK_SEPARATOR, SymbolType::TERMINAL));
        ll1_stack.push(Symbol(ProductionType::EXP, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(TokenType::TK_BEG_DELIMITER, SymbolType::TERMINAL));
        ll1_stack.push(Symbol(ProductionType::FUNC2, SymbolType::NON_TERMINAL));
        break;
        
        case 15: //FUNC → FUNC1 <(> EXP <)>
        ll1_stack.push(Symbol(TokenType::TK_END_DELIMITER, SymbolType::TERMINAL));
        ll1_stack.push(Symbol(ProductionType::EXP, SymbolType::NON_TERMINAL));
        ll1_stack.push(Symbol(TokenType::TK_BEG_DELIMITER, SymbolType::TERMINAL));
        ll1_stack.push(Symbol(ProductionType::FUNC1, SymbolType::NON_TERMINAL));
        break;

        case 16: //FUNC1 → abs
        ll1_stack.push(Symbol(TokenType::TK_ABS, SymbolType::TERMINAL));
        break;
        
        case 17: //FUNC1 → sqrt
        ll1_stack.push(Symbol(TokenType::TK_SQRT, SymbolType::TERMINAL));
        break;

        case 18: //FUNC1 → tan
        ll1_stack.push(Symbol(TokenType::TK_TAN, SymbolType::TERMINAL));
        break;
        
        case 19: //FUNC1 → sin
        ll1_stack.push(Symbol(TokenType::TK_SIN, SymbolType::TERMINAL));
        break;

        case 20: //FUNC1 → round
        ll1_stack.push(Symbol(TokenType::TK_ROUND, SymbolType::TERMINAL));
        break;
        
        case 21: //FUNC1 → cos
        ll1_stack.push(Symbol(TokenType::TK_COS, SymbolType::TERMINAL));
        break;

        case 22: //  FUNC2 → log
        ll1_stack.push(Symbol(TokenType::TK_LOG, SymbolType::TERMINAL));
        break;

        default:
         throw SynException(*tkn, "you must insert a valid symbols sequence");
          break;
      }
    }else{
      throw SynException(*tkn, "the parser stack has broken");
    }
  }

  cout << "Parser Finalizado Com Sucesso !" << "nTokens: " << count << endl;
}
