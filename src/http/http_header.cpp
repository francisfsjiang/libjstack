//
// Created by Neveralso on 15/5/2.
//

//  References
//  rfc7230 http://tools.ietf.org/html/rfc7230
//  rfc3986 http://tools.ietf.org/html/rfc3986
//  rfc7231 http://tools.ietf.org/html/rfc7231

//  ALPHA (letters)
//  CR (carriage return)
//  CRLF (CR LF)
//  CTL (controls)
//  DIGIT (decimal 0-9)
//  DQUOTE (double quote)
//  HEXDIG (hexadecimal 0-9/A-F/a-f)
//  HTAB (horizontal tab), LF (line feed)
//  OCTET (any 8-bit sequence of data)
//  SP (space)
//  VCHAR (any visible [USASCII] character)//

//  HTTP-version = HTTP-name "/" DIGIT "." DIGIT
//  HTTP-name     = %x48.54.54.50 ; "HTTP", case-sensitive//

//  https-URI    = "https:" "//" authority path-abempty [ "?" query ] [ "#" fragment ]
//  CR           = \r
//  LF           = \n
//  SP           = Space
//  HTTP-message = start-line
//                 *( header-field CRLF )
//                 CRLF
//                 [ message-body ]//

//  start-line   = request-line / status-line
//  request-line = method SP request-target SP HTTP-version CRLF
//  status-line  = HTTP-version SP status-code SP reason-phrase CRLF
//  status-code  = 3DIGIT//
//

//  header-field   = field-name ":" OWS field-value OWS
//  field-name     = token
//  field-value    = *( field-content / obs-fold )
//  field-content  = field-vchar [ 1*( SP / HTAB ) field-vchar ]
//  field-vchar    = VCHAR / obs-text
//  obs-fold       = CRLF 1*( SP / HTAB )
//                   ; obsolete line folding

#include "demoniac/http/http_header.h"

namespace demoniac{
namespace http{





}
}
