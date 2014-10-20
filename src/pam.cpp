#include "pam.hpp"

PamTransaction::PamTransaction(std::string service) {
  struct pam_conv pc = {&converse, this};
	int result = pam_start(service.c_str(), NULL, &pc, &pamh);
  switch (result) {
    case PAM_SUCCESS:
      break;
    case PAM_ABORT:
      throw std::runtime_error("General failure");
    case PAM_BUF_ERR:
      throw std::runtime_error("Memory buffer error");
    case PAM_SYSTEM_ERR:
      throw std::runtime_error("System error");
    default:
      throw std::logic_error("Unrecognized response");
  }
}

PamTransaction::~PamTransaction() {
  if (pamh != NULL) {
    pam_end(pamh, PAM_SUCCESS);
  }
}

bool PamTransaction::authenticate(std::string username_, std::string password_) {
  username = username_;
  password = password_;
  int result = pam_authenticate(pamh, PAM_DISALLOW_NULL_AUTHTOK);
  return (result == PAM_SUCCESS);
}

// Assumptions:
//   A password is asked for by requesting input without echoing
//   A username is asked for by requesting input _with_ echoing
int PamTransaction::converse(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr) {
  PamTransaction* transptr = reinterpret_cast<PamTransaction*>(appdata_ptr);

  // parameter sanity checking
  if (!resp || !msg) return PAM_CONV_ERR;

  struct pam_response *response = new struct pam_response[num_msg];
  for (int i = 0; i < num_msg; i++) {
    // initialize to safe values
    response[i].resp_retcode = 0;
    response[i].resp = 0;

    // select response based on requested output style
    switch (msg[i]->msg_style) {
      case PAM_PROMPT_ECHO_ON:
        response[i].resp = strdup((transptr->username).c_str());
        break;
      case PAM_PROMPT_ECHO_OFF:
        response[i].resp = strdup((transptr->password).c_str());
        break;
      default:
        delete[] response;
        return PAM_CONV_ERR;
    }
  }
  // everything okay, set PAM response values
  *resp = response;
  return PAM_SUCCESS;
}
