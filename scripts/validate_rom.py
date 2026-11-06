#!/usr/bin/env python3
import argparse, hashlib, json
from pathlib import Path
p=argparse.ArgumentParser(); p.add_argument('rom',type=Path); a=p.parse_args()
b=a.rom.read_bytes()
if len(b)<192: raise SystemExit('ROM truncada')
r={'size':len(b),'title':b[0xa0:0xac].decode('ascii',errors='replace'),'game_code':b[0xac:0xb0].decode('ascii',errors='replace'),'revision':b[0xbc],'sha1':hashlib.sha1(b).hexdigest(),'sha256':hashlib.sha256(b).hexdigest(),'header_checksum_ok':((-sum(b[0xa0:0xbd])-0x19)&255)==b[0xbd]}
r['matches_documented_USA']=r['sha256']=='a8bb331a6f0ff7af4387df9ac8566ae395863c2f79a5a597528a64c8bff57941'
print(json.dumps(r,indent=2))
if not r['header_checksum_ok'] or not r['matches_documented_USA']: raise SystemExit(1)
