/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
// This file contains your configuration used to connect to Cloud IoT Core

// Wifi network details.
const char *ssid = "PKI-IEEE Wi-Fi";
const char *password = "HerbertDetloff";

// Cloud iot details.
const char *project_id = "parkinglottech-267605";
const char *location = "us-central1";
const char *registry_id = "my-registry";
const char *device_id = "my-device";

// Configuration for NTP
const char* ntp_primary = "pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// To get the private key run (where private-key.pem is the ec private key
// used to create the certificate uploaded to google cloud iot):
// openssl ec -in <private-key.pem> -noout -text
// and copy priv: part.
// The key length should be exactly the same as the key length bellow (32 pairs
// of hex digits). If it's bigger and it starts with "00:" delete the "00:". If
// it's smaller add "00:" to the start. If it's too big or too small something
// is probably wrong with your key.
const char *private_key_str =
    "6e:b8:17:35:c7:fc:6b:d7:a9:cb:cb:49:7f:a0:67:"
    "63:38:b0:90:57:57:e0:c0:9a:e8:6f:06:0c:d9:ee:"
    "31:41";

// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 3600; // Maximum 24H (3600*24)

// To get the certificate for your region run:
//   openssl s_client -showcerts -connect mqtt.googleapis.com:8883
// for standard mqtt or for LTS:
//   openssl s_client -showcerts -connect mqtt.2030.ltsapis.goog:8883
// Copy the certificate (all lines between and including ---BEGIN CERTIFICATE---
// and --END CERTIFICATE--) to root.cert and put here on the root_cert variable.

const char *root_cert =
"-----BEGIN CERTIFICATE-----\n"
"MIIC+DCCAeCgAwIBAgIJAI/AXssmjBpMMA0GCSqGSIb3DQEBCwUAMBExDzANBgNV\n"
"BAMMBnVudXNlZDAeFw0yMDAyMDgwNjQwMTlaFw0yMDAzMDkwNjQwMTlaMBExDzAN\n"
"BgNVBAMMBnVudXNlZDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL4J\n"
"4wL2imRSEEHt6mQ25AW1sfcpcEplGGrikMyG4np66g5InKuS51S+Jk99JdHYoE3U\n"
"fXaxNozG5kO1+P32ihO/MmkYA+oyu1+DMzvE4uWUGSm1dLo3EM71sVi4+HQy10tE\n"
"DtIQQtw6EAf8nSgj0z/NhiaEOCmgcnYaVoBdJpz7hZjmEKHjOuK++VCd2AUB/QjL\n"
"C62aKl3KSmI43cSiPll8IpNIXyiyEFheE4alSMoZst0Rv8+AiDSP/hhgCregPdEl\n"
"5N6/dVWYuzLz6HxpAoEVuwIx7BiKMVAaZtNnwIzy4p/M390WvWYQaNhGLfTqiWI1\n"
"tOEJlZQVfhqYLhymXA8CAwEAAaNTMFEwHQYDVR0OBBYEFPdCwrzYUpIcqJJkQwrV\n"
"HxBPqfPyMB8GA1UdIwQYMBaAFPdCwrzYUpIcqJJkQwrVHxBPqfPyMA8GA1UdEwEB\n"
"/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEBAAroKLLU5yJEisVHSr9IyJDqeLT0\n"
"IuRoAYpxJGYHQbBlCnwffWO9uMW+ukdz/V/phIf+9tbBFgC/SVKJmN0eHgCwQBQZ\n"
"Sb3BLfjN+2CiY1QaG/0sn2KP0vg8BFIohXDLVhStMYSIUV6r5UW4mRo2RFCIVKLr\n"
"T18pGI998jrVqk+0/jb77BJQEBO1hfCOobQwFsQXLsThg9WnC55IcUqg7MJpZPh6\n"
"6Ejjrf8uP1EuU7uIjNUvcF0byVyXGv6NL6uE/dUeeeBbbaI+CF/ARk5Li+iDa7ZR\n"
"lLwnuDi0BJAbE/Yq3EyYZqNvUq1P4DZtZImc7vFBkg2eb02gs1WEKEIFahw=\n"
"-----END CERTIFICATE-----\n";

// In case we ever need extra topics
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];
//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};
