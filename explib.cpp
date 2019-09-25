#ifndef EXPLIB_H
#define EXPLIB_H

/*
*  explib.hpp      ---- graph algorithms library ----
*/

#include <stdio.h>
#include <stdlib.h>

#include "msclib.hpp"

int export_piece_to_pdf(const Piece & piece) {
	/**TODO**/
    system("(exec lilypond --silent >/dev/null)");
    /*insert command to print piece into pdf*/
	return 0;
}

int main () {
    Piece piece;
    export_piece_to_pdf(piece);
}

#endif
