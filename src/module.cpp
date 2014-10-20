#include <Rcpp.h>
#include <pam.hpp>

RCPP_MODULE(pam) {
  Rcpp::class_<PamTransaction>("pam")
    .constructor<std::string>()
    .method("authenticate", &PamTransaction::authenticate);
}
