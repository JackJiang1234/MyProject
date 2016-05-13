all:
	gcc -g -std=c99 -Wall -DTOKEN_PARSER_TEST token_parser.c -o token_parser_test
	gcc -g -std=c99 -Wall -DEXPR_PARSER_TEST expr_parser.c token_parser.c -o expr_parser_test
	gcc -g -std=c99 -Wall expr_parser.c token_parser.c cal.c -o cal_test
clean:
	rm -f *test
