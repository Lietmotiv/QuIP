
#include "quip_config.h"

/* utilities for manipulating strings of arbitrary length */

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <stdio.h>

#include "strbuf.h"
#include "getbuf.h"

void enlarge_buffer(String_Buf *sbp,size_t size)
{
	char *newbuf;

	size += 32;	/* give us some headroom */

//fprintf(stderr,"enlarge_buffer calling Getbuf\n");
	newbuf = (char*) getbuf(size);
	if( sbp->sb_size > 0 ){
		/* copy old contents */
		memcpy(newbuf,sbp->sb_buf,sbp->sb_size);
		givbuf(sbp->sb_buf);
	} else {
		/* if this is a new buffer, initialize w/ null string.
		 * This insures that cat_string will work to a null stringbuf.
		 */
		*newbuf=0;
	}

	sbp->sb_buf = newbuf;
	sbp->sb_size = size;
}

void copy_string(String_Buf *sbp,const char* str)
{
	if( strlen(str)+1 > sbp->sb_size )
		enlarge_buffer(sbp,(int)strlen(str)+1);
	strcpy(sbp->sb_buf,str);
}

void copy_strbuf(String_Buf *dst_sbp,String_Buf *src_sbp)
{
	u_int n;

	if( src_sbp->sb_size == 0 ) return;	/* nothing to copy */

	if( dst_sbp->sb_size < (n=(int)strlen(src_sbp->sb_buf)+1) )
		enlarge_buffer(dst_sbp,n);

	strcpy(dst_sbp->sb_buf,src_sbp->sb_buf);
}

void cat_string(String_Buf *sbp,const char *str)
{
	u_int need;

	if( (need=(int)(strlen(sbp->sb_buf)+strlen(str)+1)) > sbp->sb_size )
		enlarge_buffer(sbp,need);
	strcat(sbp->sb_buf,str);
}

void cat_string_n(String_Buf *sbp, const char *str, int n)
{
	u_int need;
	if( (need=(int)(strlen(sbp->sb_buf)+n+1)) > sbp->sb_size )
		enlarge_buffer(sbp,need);
	strncat(sbp->sb_buf,str,n);
}

String_Buf *new_stringbuf(void)
{
	String_Buf *sbp;

//fprintf(stderr,"new_stringbuf calling Getbuf\n");
	sbp = (String_Buf *)getbuf(sizeof(String_Buf));
	SET_SB_BUF(sbp, NULL);
	SET_SB_SIZE(sbp, 0);

	return(sbp);
}

void rls_stringbuf(String_Buf *sbp)
{
	if( sbp->sb_buf != NULL )
		givbuf(sbp->sb_buf);
	givbuf(sbp);
}

