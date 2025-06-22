- Khi exec được gọi trong tiến trình con, tiến trình đó bị thay thế hoàn toàn bằng chương trình mới (ví dụ: ls - hoặc date).
- Mã và dữ liệu cũ bị thay thế, nhưng PID vẫn giữ nguyên.
- Nếu exec thành công, các dòng lệnh sau exec sẽ không được thực hiện.
- Nếu exec thất bại, nó trả về -1, và chương trình vẫn tiếp tục chạy như thường.
    