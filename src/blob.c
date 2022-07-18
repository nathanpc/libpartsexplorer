/**
 * blob.c
 * Abstract representation of a binary file in memory.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "blob.h"
#include <stdio.h>
#include <stdint.h>

/**
 * Initializes a blob object.
 * 
 * @param blob Blob object to be initialized.
 */
void blob_init(pecan_blob_t *blob) {
	blob->len = 0;
	blob->data = NULL;
}

/**
 * Slurps up a file into a blob.
 *
 * @param  blob  Blob to get the contents of the file into.
 * @param  fpath File to be read into the blob.
 * @return       Number of bytes read from the file or 0 if an error occured.
 */
size_t blob_slurp(pecan_blob_t *blob, const char *fpath) {
	FILE *fh;
	size_t nbytes = 0;

	// Open the file.
	fh = fopen(fpath, "rb");
	if (fh == NULL)
		return 0L;

	// Seek file to determine its size.
	fseek(fh, 0L, SEEK_END);
	nbytes = ftell(fh);
	rewind(fh);

	// Allocate the space to read the file into.
	blob->data = realloc(blob->data, nbytes);
	if (blob->data == NULL)
		return 0L;
	
	// Read the file into the blob.
	blob->len = fread(blob->data, 1, nbytes, fh);
	if (blob->len != nbytes)
		blob_free(blob);

	// Clean up and return.
	fclose(fh);
	return blob->len;
}

/**
 * Cleans up the mess left behind by a blob object.
 * 
 * @param blob Blob object to be freed.
 */
void blob_free(pecan_blob_t *blob) {
	free(blob->data);
	blob->data = NULL;
	blob->len = 0;
}
