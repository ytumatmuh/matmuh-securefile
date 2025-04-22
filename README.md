# SecureFile

This project is part of a larger website focused on securing file uploads by detecting known malicious files using hash comparisons.

## What It Does

It acts as a gatekeeper for uploaded files—intercepting each upload and determining whether it should be allowed or blocked based on known malware signatures. By calculating the hash of each file and comparing it against a locally stored list of malicious hashes, the system can automatically decline uploads identified as threats or allow safe files to pass through.

Periodically (every 24 hours), the system downloads updated lists of malware hashes from external sources such as MalwareBazaar’s public hash feeds. These hashes are stored locally for quick and efficient reference.

## How It Works

### Daily Update
- The system fetches new hash lists from malware intelligence sites (e.g., MalwareBazaar) once every 24 hours to ensure the data is current.
- These hashes are stored locally to allow for fast lookups without relying on external API calls during uploads.

### File Upload Check
- When a file is uploaded to the website, its hash (e.g., SHA-256) is calculated.
- This hash is then checked against the locally stored list of known malware hashes.
- If a match is found:
  - The file is marked as malicious.
  - Appropriate actions are triggered (e.g., blocking the upload, logging the incident, alerting an admin).
- If there's no match:
  - The file is considered clean.
  - It is allowed to proceed through the upload process.

This logic allows the site to automatically and efficiently block known malicious files without relying on real-time API calls, ensuring performance and reliability.

