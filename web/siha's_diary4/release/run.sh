#!/bin/sh

which sqlite3 > /dev/null
if [ $? -ne 0 ]; then
    echo "install sqlite3"
    exit 1
fi

db_file_name="/tmp/5up3r_53cur3_db_l0c4710n.db"
db_path="sqlite:///$db_file_name"
flag="GuardianCTF{n3v3r_l34k_y0ur_617_d1r3c70ry}"

export SECRET_KEY="51h4_5up3r_53cr37_fl45k_k3y_h4h4_h0h0"
export DB_PATH=$db_path

if [ -e $db_file_name ]; then
    rm $db_file_name
fi

echo ".databases" | sqlite3 $db_file_name > /dev/null
chmod +w $db_file_name

python -c "from app import db, GuestBookEntry; db.create_all(); db.session.add(GuestBookEntry(username='siha', title='secret', content='$flag')); db.session.commit();"

