#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ccn/ccn.h>
#include <ccn/charbuf.h>
#include <ccn/coding.h>
#include <ccn/face_mgmt.h>
#include <ccn/sockcreate.h>
#include <ccn/reg_mgmt.h>

/**
 * This is for testing.
 *
 * Reads ccnb-encoded data from stdin and 
 * tries parsing with various parsers, and when successful turns
 * the result back into ccnb and tests for goodness.
 *
 */
int
main (int argc, char **argv)
{
	unsigned char buf[1000];
	ssize_t size;
	struct ccn_face_instance *face_instance;
        struct ccn_forwarding_entry *forwarding_entry;
        int res = 1;
        struct ccn_charbuf *c = ccn_charbuf_create();

	size = read(0, buf, sizeof(buf));
	if (size < 0)
		exit(0);
	
        face_instance = ccn_face_instance_parse(buf, size);
	if (face_instance != NULL) {
		printf("face_instance OK\n");
                c->length = 0;
                res = ccnb_append_face_instance(c, face_instance);
                if (res != 0)
                    printf("face_instance append failed\n");
                if (memcmp(buf, c->buf, c->length) != 0)
                    printf("face_instance mismatch\n");
                ccn_face_instance_destroy(&face_instance);
                face_instance = ccn_face_instance_parse(c->buf, c->length);
                if (face_instance == NULL) {
                    printf("face_instance reparse failed\n");
                    res = 1;
                }
	}
	ccn_face_instance_destroy(&face_instance);
        
        forwarding_entry = ccn_forwarding_entry_parse(buf, size);
        if (forwarding_entry != NULL) {
		printf("forwarding_entry OK\n");
                c->length = 0;
                res = ccnb_append_forwarding_entry(c, forwarding_entry);
                if (res != 0)
                    printf("forwarding_entry append failed\n");
                if (memcmp(buf, c->buf, c->length) != 0)
                    printf("forwarding_entry mismatch\n");
                ccn_forwarding_entry_destroy(&forwarding_entry);
                forwarding_entry = ccn_forwarding_entry_parse(c->buf, c->length);
                if (forwarding_entry == NULL) {
                    printf("forwarding_entry reparse failed\n");
                    res = 1;
                }
	}
        ccn_forwarding_entry_destroy(&forwarding_entry);
        
        if (res != 0) {
                printf("URP\n");
        }
	exit(res);
}