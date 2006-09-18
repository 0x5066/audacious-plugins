#include "mpg123.h"

/*
 * common.h
 */

extern void print_id3_tag(unsigned char *buf);
extern unsigned long firsthead;
extern double compute_tpf(struct frame *fr);
extern double compute_bpf(struct frame *fr);
extern long compute_buffer_offset(struct frame *fr);

/*
struct bitstream_info {
  int bitindex;
  unsigned char *wordpointer;
};
*/

extern void parse_url(const gchar * url, gchar ** user, gchar ** pass,
          gchar ** host, gint * port, gchar ** filename);
