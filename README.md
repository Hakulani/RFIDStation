# RFID Station
The system picks up boxes with indicator LED and checks by RFID.

This is the arduino code to read RFID card using RC-522 RFID module and LED 
Module
1.Master Board</br>
2.Check RFID Card Board</br>
3.Slave Board</br>

1.การทำงานจะใช้การส่งคำสั่งในการเลือก Stationและสั่งให้หลอด LED ติด</br>
2.เมื่อทำการหยิบ RFID จะตรวจสอบสัญญาณ Card ที่หายไป หากถูกต้องไฟสีเขียวหายไป
แต่ถ้าหยิบผิดไฟแดงจะติด</br>
3.ทำการตรวจสอบอีกรอบที่ Station Check ถ้าหยิบมาถูกไฟเขียวจะติด ถ้าหยิบมาผิดไฟแดงจะติด</br>
4.ระบบจะ Re set เมื่อมีคำสั่งเลือก Station ถัดไป </br>

Video : https://youtu.be/Yw-I72qVLmQ

[![Watch the video](https://img.youtube.com/vi/Yw-I72qVLmQ/maxresdefault.jpg)](https://youtu.be/Yw-I72qVLmQ)



