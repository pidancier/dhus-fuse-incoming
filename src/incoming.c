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

char ql_path[1024];
char th_path[1024];

static int inc_getattr(const char *path, struct stat *stbuf) {
	memset(stbuf, 0, sizeof(struct stat));

	int len = strlen(path);
	char *ext = strrchr(path, '.');
	if (ext && len-(ext-path) == 4) { // .jpg | .zip
		stbuf->st_mode = S_IFREG | 0644;
		stbuf->st_nlink = 1;
		if (!strcmp(ext-2, "ql.jpg")) {
			stbuf->st_size = 6421;
		}
		else if (!strcmp(ext-2, "th.jpg")) {
			stbuf->st_size = 659;
		}
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
        char *ext = strrchr(path, '.');
        if (ext && !strcmp(ext, ".jpg")) {
		if (!strcmp(ext-2, "ql.jpg")) {
			fi->fh = open(ql_path, O_RDONLY);
			if (!(fi->fh)) {
				return -errno;
			}
		}
		else if (!strcmp(ext-2, "th.jpg")) {
			fi->fh = open(th_path, O_RDONLY);
			if (!(fi->fh)) {
				return -errno;
			}
		}
		else {
			fi->fh = 0;
		}
	}
	else {
		fi->fh = 0;
	}
	return 0;
}

static int inc_release(const char *path, struct fuse_file_info *fi) {
	if (fi->fh) {
		close(fi->fh);
	}
	return 0;
}

static int inc_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi) {
	(void) path;
	if (fi->fh) {
		return read(fi->fh, buf, size);
	}
	return 0;
}

static struct fuse_operations inc_oper = {
	.getattr	= inc_getattr,
	.readdir	= inc_readdir,
	.open		= inc_open,
	.release	= inc_release,
	.read		= inc_read,
};

int main(int argc, char *argv[]) {
	getcwd(ql_path, 997);
	getcwd(th_path, 997);
	strcat(ql_path, "/ql.jpg");
	strcat(th_path, "/th.jpg");
	return fuse_main(argc, argv, &inc_oper, NULL);
}

