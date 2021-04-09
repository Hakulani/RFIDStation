# RFID Station
The system picks up boxes with indicator LED and checks by RFID.

This is the arduino code to read RFID card using RC-522 RFID module and LED 
Module
1.Master Board</br>
2.Check RFID Card Board</br>
3.Slave Board</br>

1.การทำงานจะใช้การส่งคำสั่งในการเลือก Stationและสั่งให้หลอด LED ติด 
![Capture](https://user-images.githubusercontent.com/61573397/114144018-0fae4280-993f-11eb-8028-543f1a21c963.JPG)
</br>

2.เมื่อทำการหยิบ RFID จะตรวจสอบสัญญาณ Card ที่หายไป หากถูกต้องไฟสีเขียวหายไป
![green pic](https://user-images.githubusercontent.com/61573397/114144363-74699d00-993f-11eb-8fc1-42c4149b796c.JPG)
</br>
แต่ถ้าหยิบผิดไฟแดงจะติด</br>
![red](https://user-images.githubusercontent.com/61573397/114144571-ac70e000-993f-11eb-8525-0f4c9139423e.JPG)</br>

3.ทำการตรวจสอบอีกรอบที่ Station Check ถ้าหยิบมาถูกไฟเขียวจะติด
![green rfid](https://user-images.githubusercontent.com/61573397/114144772-e04c0580-993f-11eb-900a-7367d9b89a0d.JPG)
</br>

<br>ถ้าหยิบมาผิดไฟแดงจะติด</br>
![red rfid](https://user-images.githubusercontent.com/61573397/114144935-11c4d100-9940-11eb-801b-9c11494c784e.JPG)
</br>

4.ระบบจะ Re-set เมื่อมีคำสั่งเลือก Station ถัดไป </br>

Video : https://youtu.be/Yw-I72qVLmQ




