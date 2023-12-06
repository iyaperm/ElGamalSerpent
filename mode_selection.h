#ifndef MODE_SELECTION_H
#define MODE_SELECTION_H

#include "ECB.h"
#include "CBC.h"
#include "CFB.h"
#include "CTR.h"
#include "OFB.h"
#include "RandomDelta.h"
#include "encryption_mode.h"
#include "iv_gen.h"

void mode_selection(std::string & user_mode, std::string & str_key, std::string & iv, std::wstring & input_file_path,
	std::wstring & output_file_path, bool& encrypt, QProgressDialog& progress_bar);

#endif // !MODE_SELECTION_H
