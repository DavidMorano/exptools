#define MSG_INTERNAL	0x01	/* print internal tool error message */
#define MSG_ERROR	0x02	/* print normal error message */
#define MSG_ALERT	0x03	/* print alert message */
#define MSG_WARN	0x04	/* print warning message */
#define MSG_NOTE	0x05	/* print a note to stdout */
#define MSG_USAGE	0x06	/* print out usage message */
#define MSG_QUESTION	0x07	/* print out a question */
#define MSG_ERRNOTE	0x08	/* print a note to stderr */
#define MSG_ASIS	0x09	/* Just print the msg as is to standard output */
#define MSG_ERRASIS	0x0a	/* Just print the msg as is to standard error */
#define MSG_DEBUG	0x0b	/* print debug message */

#define MSG_CONTINUE	0x10	/* continue a previous message -- */
				/* can be OR'ed with other types */

#define MSG_MASK	0x0f	/* mask for getting message type */

#define MSG_INDENT(x)	((x) << 8)	/* indentation for messages */
