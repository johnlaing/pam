loadModule("pam", TRUE)

pam.auth <- function(service, username, password) {
    new(pam, service)$authenticate(username, password)
}
