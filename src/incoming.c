/*
  incoming.c - FUSE implementation
  Copyright (C) 2016      Jonathan Bayle <jonathan.bayle@gael.fr>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define FUSE_USE_VERSION 26
#include <fuse.h>

static int inc_getattr(const char *path, struct stat *stbuf) {
	memset(stbuf, 0, sizeof(struct stat));

	int len = strlen(path);
	char *ext = strrchr(path, '.');
	if (ext && len-(ext-path) == 4) { // .jpg | .zip
		stbuf->st_mode = S_IFREG | 0644;
		stbuf->st_nlink = 1;
	}
	else {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	}
	stbuf->st_uid = getuid();
	stbuf->st_uid = getuid();
	stbuf->st_atime = stbuf->st_mtime = stbuf->st_ctime = time(NULL);
	return 0;
}

static int inc_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi) {
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0) {
		return -ENOENT;
	}

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);

	return 0;
}

static int inc_open(const char *path, struct fuse_file_info *fi) {
	(void) path;
	(void) fi;
	return 0;
}

static int inc_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi) {
	(void) path;
	(void) buf;
	return 0;
}

static struct fuse_operations inc_oper = {
	.getattr	= inc_getattr,
	.readdir	= inc_readdir,
	.open		= inc_open,
	.read		= inc_read,
};

int main(int argc, char *argv[]) {
	return fuse_main(argc, argv, &inc_oper, NULL);
}

