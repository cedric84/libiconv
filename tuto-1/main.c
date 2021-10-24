/**
 * @brief		The application entry point.
 * @file
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <iconv.h>

/**
 * @brief		UCS-4 to ASCII conversions.
 */
static void
fct0(void)
{
	//---Definitions---//
	static const char*	to_code_arr[]	= {
		"ANSI_X3.4-1968",
		"US-ASCII",
		"ASCII",
	};
	static const size_t	to_code_arr_cnt	= sizeof(to_code_arr) / sizeof(to_code_arr[0]);

	//---Loop over each conversion to do---//
	for (size_t to_code_arr_idx = 0; to_code_arr_idx < to_code_arr_cnt; to_code_arr_idx++) {
		//---Create the conversion descriptor---//
		const char*	to_code	= to_code_arr[to_code_arr_idx];
		iconv_t		cd;
		assert(((iconv_t)-1)	!= (cd = iconv_open(to_code, "UCS-4LE")));

		//---Loop over each possible value---//
		for (uint32_t ucs4 = 0; ucs4 < 0x80; ucs4++) {
			//---Convert---//
			char	to_txt[2];
			char*	in		= (char*)&ucs4;
			size_t	in_sz	= sizeof(ucs4);
			char*	out		= to_txt;
			size_t	out_sz	= sizeof(to_txt);
			assert(0					== iconv(cd, &in, &in_sz, &out, &out_sz));
			assert(0					== in_sz);
			assert(sizeof(to_txt)-1		== out_sz);
			assert(&(to_txt[1])			== out);
			assert(to_txt[0]			== ucs4);
		}

		//---Fail to convert an out-of-bound value---//
		{
			uint32_t	ucs4	= 0x80;
			char		to_txt[2];
			char*		in		= (char*)&ucs4;
			size_t		in_sz	= sizeof(ucs4);
			char*		out		= to_txt;
			size_t		out_sz	= sizeof(to_txt);
			assert((size_t)-1			== iconv(cd, &in, &in_sz, &out, &out_sz));
			assert(sizeof(ucs4)			== in_sz);
			assert(sizeof(to_txt)		== out_sz);
			assert(&(to_txt[0])			== out);
		}

		//---Release memory---//
		assert(0	== iconv_close(cd));
	}
}

/**
 * @brief		The application entry point.
 * @param		[in]	argc	The number of arguments.
 * @param		[in]	argv	The arguments values.
 * @return		Returns EXIT_SUCCESS on success.
 */
extern int
main(int argc, char* argv[])
{
	//---Log---//
	printf("%s started\n", __func__);
	printf("libiconv version: %u.%u\n", _LIBICONV_VERSION >> 8, 0xFFU & _LIBICONV_VERSION);

	//---Check the version---//
	assert(_LIBICONV_VERSION	== _libiconv_version);

	//---Run---//
	fct0();

	//---Return---//
	printf("%s terminated\n", __func__);
	return EXIT_SUCCESS;
}
