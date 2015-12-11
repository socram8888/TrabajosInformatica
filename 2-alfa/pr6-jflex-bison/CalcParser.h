#pragma once

namespace Calc {
	class Parser {
		public:
			Parser() : parser(scanner) {}
		
			int parse() {
				return parser.parse();
			}
		
		private:
			Calc::FlexScanner scanner;
			Calc::BisonParser parser;
	};
}
