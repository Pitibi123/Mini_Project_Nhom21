README - GIỚI THIỆU TRÒ CHƠI BỊT MẮT BẮT DÊ

1. Giới thiệu chung

Bịt mắt bắt dê là một trò chơi dân gian quen thuộc ở Việt Nam. Trò chơi thường được tổ chức trong các hoạt động tập thể, sinh hoạt ngoài trời hoặc các dịp vui chơi truyền thống. Điểm đặc trưng của trò chơi là một người chơi sẽ bị bịt mắt và phải tìm cách bắt được những người chơi khác đang đóng vai “dê”.

Trong trò chơi thực tế, người bịt mắt không thể nhìn thấy nên phải dựa vào âm thanh, cảm nhận phương hướng và phản ứng của những người xung quanh để phán đoán vị trí của dê. Ngược lại, những người làm dê cần di chuyển khéo léo, tránh bị bắt, đồng thời phải giữ khoảng cách hợp lý với những người chơi khác.

2. Ý tưởng trò chơi

Trò chơi có hai nhóm vai trò chính:

- Người bịt mắt: là người đi bắt dê.
- Dê: là những người chơi còn lại, có nhiệm vụ né tránh người bịt mắt.

Người bịt mắt chiến thắng khi bắt được một dê bất kỳ. Dê chiến thắng khi không bị người bịt mắt bắt trong thời gian quy định. Trong phiên bản mô phỏng nhiều dê, có thể xảy ra trường hợp người bịt mắt bắt được một dê khác, nhưng người chơi đang xét vẫn được xem là sống sót.

3. Bối cảnh mô phỏng

Trong mini project này, trò chơi bịt mắt bắt dê được mô phỏng trên một bản đồ dạng lưới hai chiều. Người bắt và các dê cùng di chuyển theo từng lượt. Ở mỗi lượt, mỗi nhân vật có thể đi lên, xuống, trái, phải hoặc đứng yên tại vị trí hiện tại.

Bản đồ có giới hạn cố định, vì vậy các nhân vật không được phép đi ra ngoài phạm vi bản đồ. Trò chơi kết thúc khi người bắt bắt được một dê hoặc khi hết số lượt quy định.

4. Luật chơi cơ bản trong mô phỏng

Các luật chính của trò chơi trong mô phỏng gồm:

- Có một người bịt mắt và nhiều dê cùng tham gia.
- Người bịt mắt và dê di chuyển trên bản đồ hai chiều.
- Mỗi lượt, nhân vật có thể di chuyển sang một ô kề cạnh hoặc đứng yên.
- Người bịt mắt bắt được dê nếu khoảng cách Manhattan giữa người bắt và dê nhỏ hơn hoặc bằng 1.
- Dê không được phép rời khỏi bản đồ.
- Dê có hướng nhìn nhất định, chỉ quan sát được những đối tượng nằm trong vùng nhìn thấy của mình.
- Nếu muốn đổi hướng nhìn, dê sẽ mất một lượt di chuyển.
- Các dê có thể va chạm với nhau nếu đứng quá gần.
- Khi hai dê va chạm, chúng bị đứng yên trong một số lượt nhất định.
- Người bịt mắt có thể nghe âm thanh từ dê nhưng không thể phân biệt chính xác từng dê.
- Người bịt mắt sẽ dựa vào âm thanh để phán đoán hướng di chuyển.

5. Điểm đặc biệt của phiên bản mô phỏng

Phiên bản mô phỏng này không chỉ tái hiện luật chơi cơ bản của trò bịt mắt bắt dê, mà còn bổ sung thêm nhiều yếu tố chiến thuật như:

- Tầm nhìn giới hạn của dê.
- Khả năng ghi nhớ vị trí ban đầu.
- Khả năng nghe âm thanh của người bắt.
- Độ trễ khi người bắt phản ứng với âm thanh.
- Va chạm giữa các dê.
- Nhiều cách chơi khác nhau dành cho dê.

Nhờ các yếu tố này, trò chơi trở nên gần với một bài toán mô phỏng chiến thuật hơn là chỉ là một trò chơi di chuyển đơn giản.

6. Mục tiêu của trò chơi trong project

Mục tiêu của project là tìm hiểu xem dê nên di chuyển như thế nào để tăng khả năng sống sót. Thay vì điều khiển dê một cách ngẫu nhiên, project xây dựng nhiều cách chơi khác nhau để so sánh hiệu quả.

Các chiến thuật của dê có thể tập trung vào những mục tiêu như:

- Giữ khoảng cách với người bắt.
- Tránh đi sát biên bản đồ.
- Tránh va chạm với các dê khác.
- Tận dụng việc người bắt không phân biệt được từng dê.
- Quan sát và ghi nhớ vị trí của các nhân vật khác.

7. Ý nghĩa của trò chơi

Trò bịt mắt bắt dê là một trò chơi đơn giản nhưng có nhiều yếu tố thú vị để mô phỏng bằng lập trình. Trò chơi có thể được dùng để minh họa các nội dung như:

- Di chuyển trên bản đồ hai chiều.
- Tính khoảng cách Manhattan.
- Xử lý va chạm giữa các đối tượng.
- Mô phỏng hành vi của nhân vật.
- So sánh các chiến thuật khác nhau.
- Ứng dụng lập trình hướng đối tượng trong thiết kế trò chơi.

8. Kết luận

Bịt mắt bắt dê là một trò chơi dân gian gần gũi, dễ hiểu nhưng có thể phát triển thành một bài toán mô phỏng thú vị. Khi đưa trò chơi vào môi trường lập trình, các yếu tố như tầm nhìn, âm thanh, va chạm, ghi nhớ và chiến thuật di chuyển giúp trò chơi trở nên sinh động hơn.

Thông qua project này, người học có thể vừa tìm hiểu một trò chơi dân gian Việt Nam, vừa rèn luyện tư duy thiết kế chương trình và mô phỏng hành vi nhân vật trong một môi trường có luật chơi cụ thể.

Link slide: https://www.canva.com/design/DAHJYsonEEc/OvUSATWTi_fGBAqloQmkKA/edit
