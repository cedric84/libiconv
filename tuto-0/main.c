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
 * @brief		Tutorial function.
 */
static void
fct0(void)
{
	//---Definitions---//
	static char			from_txt[]		= "c\xe9" "dric";
	static const char*	from_code		= "ISO-8859-1";
	static const char*	to_code_arr[]	= {
		"UTF-8",
		"UTF-16LE",
		"UTF-16BE",
		"UTF-16",
	};
	static const size_t	to_code_arr_cnt	= sizeof(to_code_arr) / sizeof(to_code_arr[0]);

	//---Loop over each conversion to do---//
	for (size_t to_code_arr_idx = 0; to_code_arr_idx < to_code_arr_cnt; to_code_arr_idx++) {
		//---Create the conversion descriptor---//
		const char*	to_code	= to_code_arr[to_code_arr_idx];
		iconv_t		cd;
		assert(((iconv_t)-1)	!= (cd = iconv_open(to_code, from_code)));

		//---Convert---//
		static char	to_txt[32];
		char*		in		= from_txt;
		size_t		in_sz	= sizeof(from_txt);
		char*		out		= to_txt;
		size_t		out_sz	= sizeof(to_txt);
		assert(0	== iconv(cd, &in, &in_sz, &out, &out_sz));

		//---Log---//
		printf("%-10s: ", to_code);
		for (const char* p = to_txt; p != out; p++) {
			printf("%02" PRIx8 " ", (uint8_t)(p[0]));
		}
		printf("\n");

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
