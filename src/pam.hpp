#include <security/pam_appl.h>
#include <string>
#include <cstring>
#include <stdexcept>

class PamTransaction {
public:
  PamTransaction(std::string service);
  ~PamTransaction();

  bool authenticate(std::string username_, std::string password_);
private:
  // disable copy constructors
  PamTransaction(const PamTransaction& other);
  PamTransaction& operator=(const PamTransaction& other);

  pam_handle_t* pamh = NULL;
  std::string username;
  std::string password;

  static int converse(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr);
};

