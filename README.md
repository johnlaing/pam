# pam: Pluggable Authentication Module support for R
===
## Usage
Persistent/longer:
```R
pam <- new("pam", "service")
pam$authenticate("user1", "pw1")
pam$authenticate("user2", "pw2")
```

Shorter:
```R
pam.auth("service", "user", "pw")
```

===
## Acknowledgment:
Design and implementation borrowed heavily from the Ruby rpam gem: https://github.com/canweriotnow/rpam-ruby19
