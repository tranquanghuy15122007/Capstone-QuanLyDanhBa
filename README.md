//đừng có lười nhé đọc hết t chuẩn bị kĩ lắm đấy ( nếu có câu hỏi sao t xóa cài này không làm cái kia thì đợi t ngủ dậy nhé mọi thứ đều có lý do)
//vibe coding (nhưng t cố cho nó đi sát với bài học trên lớp rồi)
//vốn dĩ full code thay đổi chỉ bởi vì cái đề bài yêu cầu load dữ liệu từ file cái quá đó mình chưa học thì cũng phải chịu thôi 
//và please nếu code thì hãy cố bám sát bài học nhất có thể đừng có AI mẫu(AI mẫu là kiểu AI kêu j code nấy ấy đừng)
//work smart not hard // vibe coding bằng AI cũng được miễn đừng có nó kêu j làm cái đấy
//mấy cái bài trong file này thật sự t đã cố gắng làm gọn lại hết mức có thể rồi thật đấy chứ t cũng đâu muốn như vậy 
//nếu thêm ý tưởng thì hãy thảo luận trước nhé vì một khi thêm thì độ khó vấn đáp sẽ tăng mà max điểm bài làm của mình có 4 thôi

log:
 cấu trúc file:
QuanlyDanhba.h - > ChucNamg.h - > HotrohienthiCSVFILE.h - > hienthi.cpp

Date.h // lớp riêng để định nghĩa birthday
file danhba.csv //chứa thông tin dữ liệu(dung notepad hoặc exel mở ra là hiểu)

 cấu trúc class:
QuanlyDanhba - > ChucNamg - > HotroHienthi - > hienthi.cpp
   lớp cha       lớp con         lớp con        

QuanlyDanhba: bao gồm chứa dữ liệu vector và các thành phần tên,sdt,quanhe,ngaysinh,ghichu(quá tải toán tử cin để làm chức năng thêm)//cho đủ yêu cầu bài th
ChucNang: bao gồm các cin chức năng như thêm xóa sửa và lọc(của ai người đó làm nhé)
HotroHienthi: bao gồm: docFileDanhBa để đọc file csv và lấy từng thành phần ten,sdt,quanhe,ngaysinh,ghichu
                       Capnhatfilekhithem khi thực hiện các chức năng xong gọi ở main() nó sẽ cập nhất lấy dữ liệu được đưa vào vector mảng
                                            //lấy cái dữ liệu đó cập nhật vô file danhba.csv
date.h: làm định nghĩa một kiểu dữ liệu trong QuanlyDanhba Date Birthday bth sẽ không được nên phải định nghĩa date lại
danhba.csv thì có nói bên trên rồi
hienthi.cpp là một file để gọi test mấy cái làm rồi thôi

//bổ sung thêm kiến thức dữ liệu cho từng hàm
-- ai rảnh thì giải thích từng hàm của từng lớp vô dây cho dễ nhớ
