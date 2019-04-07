/*
to compile on my computer:
compile: g++ curl_email.cpp -lcurl -o ./test
run: ./test [email we are CC'ing]
 */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>
using namespace std;

#define FROM_ADDR    "<project.ariadne2270@gmail.com>"
#define TO_ADDR      "<project.ariadne2270@gmail.com>"
#define CC_ADDR      "<project.ariadne2270@gmail.com>"

#define FROM_MAIL "Project Ariadne" FROM_ADDR
#define TO_MAIL   "Emergency Contact Alert" TO_ADDR
#define CC_MAIL   "Emergency Contact Alert" CC_ADDR

static const char *payload_text[] = {
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
  "To: " TO_MAIL "\r\n",
  "From: " FROM_MAIL "\r\n",
  "Cc: " CC_MAIL "\r\n",
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
  "rfcpedant.example.org>\r\n",
  "Subject: ALERT! Checkin Timeout Exceed.\r\n",
  "\r\n", /*BODY OF MESSAGE STARTS AFTER THIS*/
  "You have been specified as an emergency contact for one of our users.\r\n",
  "This user did not check in prior to the expiration of their emergency timer.\r\n",
  "\r\n",
  "-Project Ariadne\r\n",
  NULL
};

struct upload_status {
  int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;

  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  data = payload_text[upload_ctx->lines_read];

  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;

    return len;
  }

  return 0;
}

int main(int argc, char* argv[])
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx;

  upload_ctx.lines_read = 0;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_USERNAME, "project.ariadne2270@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "CSCI2270S19");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);

    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, TO_ADDR);
    // recipients = curl_slist_append(recipients, CC_ADDR);
    recipients = curl_slist_append(recipients, argv[1]);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Free the list of recipients */
    curl_slist_free_all(recipients);

    curl_easy_cleanup(curl);
  }

  return (int)res;
}
