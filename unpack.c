#include "unpack.h"

static BYTE palette[] = {
0xff,0xff,0xff,0xff,0xff,0xcc,0xff,0xff,0x99,0xff,0xff,0x66,0xff,0xff,0x33,
0xff,0xff,0x00,0xff,0xcc,0xff,0xff,0xcc,0xcc,0xff,0xcc,0x99,0xff,0xcc,0x66,
0xff,0xcc,0x33,0xff,0xcc,0x00,0xff,0x99,0xff,0xff,0x99,0xcc,0xff,0x99,0x99,
0xff,0x99,0x66,0xff,0x99,0x33,0xff,0x99,0x00,0xff,0x66,0xff,0xff,0x66,0xcc,
0xff,0x66,0x99,0xff,0x66,0x66,0xff,0x66,0x33,0xff,0x66,0x00,0xff,0x33,0xff,
0xff,0x33,0xcc,0xff,0x33,0x99,0xff,0x33,0x66,0xff,0x33,0x33,0xff,0x33,0x00,
0xff,0x00,0xff,0xff,0x00,0xcc,0xff,0x00,0x99,0xff,0x00,0x66,0xff,0x00,0x33,
0xff,0x00,0x00,0xcc,0xff,0xff,0xcc,0xff,0xcc,0xcc,0xff,0x99,0xcc,0xff,0x66,
0xcc,0xff,0x33,0xcc,0xff,0x00,0xcc,0xcc,0xff,0xcc,0xcc,0xcc,0xcc,0xcc,0x99,
0xcc,0xcc,0x66,0xcc,0xcc,0x33,0xcc,0xcc,0x00,0xcc,0x99,0xff,0xcc,0x99,0xcc,
0xcc,0x99,0x99,0xcc,0x99,0x66,0xcc,0x99,0x33,0xcc,0x99,0x00,0xcc,0x66,0xff,
0xcc,0x66,0xcc,0xcc,0x66,0x99,0xcc,0x66,0x66,0xcc,0x66,0x33,0xcc,0x66,0x00,
0xcc,0x33,0xff,0xcc,0x33,0xcc,0xcc,0x33,0x99,0xcc,0x33,0x66,0xcc,0x33,0x33,
0xcc,0x33,0x00,0xcc,0x00,0xff,0xcc,0x00,0xcc,0xcc,0x00,0x99,0xcc,0x00,0x66,
0xcc,0x00,0x33,0xcc,0x00,0x00,0x99,0xff,0xff,0x99,0xff,0xcc,0x99,0xff,0x99,
0x99,0xff,0x66,0x99,0xff,0x33,0x99,0xff,0x00,0x99,0xcc,0xff,0x99,0xcc,0xcc,
0x99,0xcc,0x99,0x99,0xcc,0x66,0x99,0xcc,0x33,0x99,0xcc,0x00,0x99,0x99,0xff,
0x99,0x99,0xcc,0x99,0x99,0x99,0x99,0x99,0x66,0x99,0x99,0x33,0x99,0x99,0x00,
0x99,0x66,0xff,0x99,0x66,0xcc,0x99,0x66,0x99,0x99,0x66,0x66,0x99,0x66,0x33,
0x99,0x66,0x00,0x99,0x33,0xff,0x99,0x33,0xcc,0x99,0x33,0x99,0x99,0x33,0x66,
0x99,0x33,0x33,0x99,0x33,0x00,0x99,0x00,0xff,0x99,0x00,0xcc,0x99,0x00,0x99,
0x99,0x00,0x66,0x99,0x00,0x33,0x99,0x00,0x00,0x66,0xff,0xff,0x66,0xff,0xcc,
0x66,0xff,0x99,0x66,0xff,0x66,0x66,0xff,0x33,0x66,0xff,0x00,0x66,0xcc,0xff,
0x66,0xcc,0xcc,0x66,0xcc,0x99,0x66,0xcc,0x66,0x66,0xcc,0x33,0x66,0xcc,0x00,
0x66,0x99,0xff,0x66,0x99,0xcc,0x66,0x99,0x99,0x66,0x99,0x66,0x66,0x99,0x33,
0x66,0x99,0x00,0x66,0x66,0xff,0x66,0x66,0xcc,0x66,0x66,0x99,0x66,0x66,0x66,
0x66,0x66,0x33,0x66,0x66,0x00,0x66,0x33,0xff,0x66,0x33,0xcc,0x66,0x33,0x99,
0x66,0x33,0x66,0x66,0x33,0x33,0x66,0x33,0x00,0x66,0x00,0xff,0x66,0x00,0xcc,
0x66,0x00,0x99,0x66,0x00,0x66,0x66,0x00,0x33,0x66,0x00,0x00,0x33,0xff,0xff,
0x33,0xff,0xcc,0x33,0xff,0x99,0x33,0xff,0x66,0x33,0xff,0x33,0x33,0xff,0x00,
0x33,0xcc,0xff,0x33,0xcc,0xcc,0x33,0xcc,0x99,0x33,0xcc,0x66,0x33,0xcc,0x33,
0x33,0xcc,0x00,0x33,0x99,0xff,0x33,0x99,0xcc,0x33,0x99,0x99,0x33,0x99,0x66,
0x33,0x99,0x33,0x33,0x99,0x00,0x33,0x66,0xff,0x33,0x66,0xcc,0x33,0x66,0x99,
0x33,0x66,0x66,0x33,0x66,0x33,0x33,0x66,0x00,0x33,0x33,0xff,0x33,0x33,0xcc,
0x33,0x33,0x99,0x33,0x33,0x66,0x33,0x33,0x33,0x33,0x33,0x00,0x33,0x00,0xff,
0x33,0x00,0xcc,0x33,0x00,0x99,0x33,0x00,0x66,0x33,0x00,0x33,0x33,0x00,0x00,
0x00,0xff,0xff,0x00,0xff,0xcc,0x00,0xff,0x99,0x00,0xff,0x66,0x00,0xff,0x33,
0x00,0xff,0x00,0x00,0xcc,0xff,0x00,0xcc,0xcc,0x00,0xcc,0x99,0x00,0xcc,0x66,
0x00,0xcc,0x33,0x00,0xcc,0x00,0x00,0x99,0xff,0x00,0x99,0xcc,0x00,0x99,0x99,
0x00,0x99,0x66,0x00,0x99,0x33,0x00,0x99,0x00,0x00,0x66,0xff,0x00,0x66,0xcc,
0x00,0x66,0x99,0x00,0x66,0x66,0x00,0x66,0x33,0x00,0x66,0x00,0x00,0x33,0xff,
0x00,0x33,0xcc,0x00,0x33,0x99,0x00,0x33,0x66,0x00,0x33,0x33,0x00,0x33,0x00,
0x00,0x00,0xff,0x00,0x00,0xcc,0x00,0x00,0x99,0x00,0x00,0x66,0x00,0x00,0x33,
0x00,0x00,0x00,0xee,0x00,0x00,0xdd,0x00,0x00,0xbb,0x00,0x00,0xaa,0x00,0x00,
0x88,0x00,0x00,0x77,0x00,0x00,0x55,0x00,0x00,0x44,0x00,0x00,0x22,0x00,0x00,
0x11,0x00,0x00,0x00,0xee,0x00,0x00,0xdd,0x00,0x00,0xbb,0x00,0x00,0xaa,0x00,
0x00,0x88,0x00,0x00,0x77,0x00,0x00,0x55,0x00,0x00,0x44,0x00,0x00,0x22,0x00,
0x00,0x11,0x00,0x00,0x00,0xee,0x00,0x00,0xdd,0x00,0x00,0xbb,0x00,0x00,0xaa,
0x00,0x00,0x88,0x00,0x00,0x77,0x00,0x00,0x55,0x00,0x00,0x44,0x00,0x00,0x22,
0xff,0xff,0xff,0xee,0xee,0xee,0xdd,0xdd,0xdd,0xbb,0xbb,0xbb,0xaa,0xaa,0xaa,
0x88,0x88,0x88,0x77,0x77,0x77,0x55,0x55,0x55,0x44,0x44,0x44,0x22,0x22,0x22,
0x11,0x11,0x11
};

static int entryInfoCmp(const void *_x, const void *_y) {
	struct entry_info_t *x = (struct entry_info_t *)_x;
	struct entry_info_t *y = (struct entry_info_t *)_y;

	if (x->id == y->id) {
		if (x->type == y->type)
			return 0;
		return ((x->type < y->type) ? -1 : 1);
	}

	return ((x->id < y->id) ? -1 : 1);
}

static struct entry_info_t *readEntryInfos(struct reader_t *r, LONG n) {
	struct entry_info_t *inf;
	LONG i;

	inf = (struct entry_info_t *)malloc2(sizeof(*inf)*n);

	for (i = 0; i < n; i++) {
		inf[i].offset = readLong(r);
		inf[i].size = readLong(r);
		inf[i].type = readLong(r);
		inf[i].id = readLong(r);
	}

	qsort(inf, n, sizeof(*inf), entryInfoCmp);

	return inf;
}

static struct entry_info_t *getEntryInfo(struct entry_info_t *is, LONG n, LONG id, LONG type) {
	LONG i;
	struct entry_info_t e;
	LONG l, r;
	LONG ip;

	e.id = id;
	e.type = type;

	l = 0;
	r = n;
	ip = 0;
	i = n/2;

	while (i != ip) {
		int c;
		c = entryInfoCmp(&e, is + i);
		if (c == 0)
			return is + i;
		if (c == -1)
			r = i;
		if (c == 1)
			l = i;

		ip = i;
		i = l + (r - l)/2;
	}

	return is + i;
}

#define WRITEB(v)	*(pBuf++) = v
BYTE *readPixelBuffer(struct reader_t *r, LONG *wP, LONG *hP) {
	BYTE *buf;
	BYTE *pBuf;
	BYTE valueW;
	BYTE blockLenW;
	LONG nPixels;
	LONG pixelIdx;
	LONG blockSize;
	LONG blockIdx;
	BIT blockType;
	BYTE value;
	LONG w, h;

	h = readShort(r);
	w = readShort(r);
	*hP = h;
	*wP = w;

	buf = (BYTE *)malloc2(w*h);
	pBuf = buf;

	readLong(r);
	valueW = readByte(r);
	blockLenW = readByte(r);

	nPixels = w*h;
	pixelIdx = 0;

	memset(buf, 0, nPixels);

	while(pixelIdx < nPixels) {
		blockType = readBit(r);
		blockSize = readBits(r, blockLenW) + 1;
		if (blockType == 1) {
			for (blockIdx = 0; blockIdx < blockSize; blockIdx++)
				WRITEB(readBits(r, valueW));
		} else {
			value = readBits(r, valueW);
			for (blockIdx = 0; blockIdx < blockSize; blockIdx++)
				WRITEB(value);
		}
		pixelIdx += blockSize;
	}
	if (pixelIdx != nPixels) {
		fprintf(stderr, "Error reading format.\n");
		exit(1);
	}

	return buf;
}

static BYTE *makeRGBBuffer(BYTE *idxBuf, BYTE *colourMap, LONG colours, LONG w, LONG h) {
	BYTE *rgbBuf;
	LONG i;

	rgbBuf = (BYTE *)malloc2(w*h*3);
	memset(rgbBuf, 0, w*h*3);

	for (i = 0; i < w*h; i++) {
		rgbBuf[i*3] = palette[colourMap[idxBuf[i]]*3 + 2];
		rgbBuf[i*3 + 1] = palette[colourMap[idxBuf[i]]*3 + 1];
		rgbBuf[i*3 + 2] = palette[colourMap[idxBuf[i]]*3];
	}

	return rgbBuf;
}

int total = 0;
int complete = 0;

static void unpackPDf5(struct entry_info_t *is, LONG n, LONG idx, struct reader_t *r, UnpackCallback f) {
	LONG bit2_id;
	LONG clrs_id;
	struct entry_info_t *bit2_e;
	struct entry_info_t *clrs_e;

	BYTE *idxBuf = NULL;
	BYTE *colourMap = NULL;
	BYTE *rgbBuf = NULL;

	LONG w, h;

	total++;

	seekReader(r, is[idx].offset);
	readLong(r);
	bit2_id = readLong(r);
	clrs_id = readLong(r);

	bit2_e = getEntryInfo(is, n, bit2_id, TYPE_Bit2);
	clrs_e = getEntryInfo(is, n, clrs_id, TYPE_Clrs);

	colourMap = (BYTE *)malloc2(clrs_e->size);
	seekReader(r, clrs_e->offset);
	readBytes(r, colourMap, clrs_e->size);

	seekReader(r, bit2_e->offset);

	idxBuf = readPixelBuffer(r, &w, &h);
	if (idxBuf == NULL)
		goto cleanup;

	rgbBuf = makeRGBBuffer(idxBuf, colourMap, clrs_e->size, w, h);
	if (rgbBuf == NULL)
		goto cleanup;

	complete++;
	f(is[idx].id, w, h, rgbBuf);
cleanup:
	if (idxBuf != NULL)
		free(idxBuf);
	if (colourMap != NULL)
		free(colourMap);
	if (rgbBuf != NULL)
		free(rgbBuf);
}

void unpack(struct reader_t *r, UnpackCallback f) {
	LONG entryCount;
	struct entry_info_t *is;
	LONG i;

	if (readShort(r) != 0xffff) {
		fprintf(stderr, "Magic not correct.\n");
		exit(1);
	}

	entryCount = readLong(r);
	readLong(r);
	readShort(r);

	is = readEntryInfos(r, entryCount);

	for (i = 0; i < entryCount; i++) {
		if (is[i].type != TYPE_PDf5)
			continue;

		unpackPDf5(is, entryCount, i, r, f);
	}

	free(is);
}