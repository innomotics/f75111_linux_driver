# Security Policy

The _Innomotics OSS_ community takes the security of its code seriously. If you
think you have found a security vulnerability, please read the next sections
and follow the instructions to report your finding.

## Security Context

Open source software can be used in various contexts that may go far beyond
what it was originally designed and also secured for. Therefore, we describe
here how this project is currently expected to be used in security-sensitive
scenarios.

As this module is providing hardware access for specific resources and running in the context of the `root` user,
all further consumers must be aware on security contexts itself.
This module should not be able to expose further hardware resources or provide writing from arbitrary users.

## Reporting a Vulnerability

Please DO NOT report any potential security vulnerability via a public channel
(mailing list, github issue etc.). Instead, contact the maintainers 
mathias.haimerl@siemens.com and nikita.votintsev@siemens.com via email
directly. Please provide a detailed description of the issue, the steps to
reproduce it, the affected versions and, if already available, a proposal for a
fix. You should receive a response within 5 working days. If the issue is
confirmed as a vulnerability by us, we will open a Security Advisory on github
and give credits for your report if desired. This project follows a 90 day
disclosure timeline.