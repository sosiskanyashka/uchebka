import cv2

def main():
    """
    Приложение для просмотра IP-камеры с применением метода вычитания фона для обнаружения движения.
    """

    
    ip_camera_url = "http://69.111.182.219:82/cgi-bin/camera?resolution=640&amp;quality=1&amp;Language=0&amp;COUNTER"  

    
    cap = cv2.VideoCapture(ip_camera_url)

    if not cap.isOpened():
        print(f"Не удалось открыть камеру по URL: {ip_camera_url}")
        return

    
    window_width = 800
    window_height = 600

   
    background_subtractor = cv2.createBackgroundSubtractorMOG2()

    
    while True:
        ret, frame = cap.read()

        if not ret:
            print("Не удалось получить кадр с камеры.  Повторное подключение...")
            cap.release()  
            cap = cv2.VideoCapture(ip_camera_url) 
            if not cap.isOpened():
                print("Повторное подключение не удалось. Выход.")
                break
            continue


        
        resized_frame = cv2.resize(frame, (window_width, window_height))

        
        foreground_mask = background_subtractor.apply(resized_frame)

        
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
        foreground_mask = cv2.morphologyEx(foreground_mask, cv2.MORPH_OPEN, kernel)
        foreground_mask = cv2.dilate(foreground_mask, kernel, iterations=2) 

        

        
        cv2.imshow("IP Camera Feed", resized_frame)
        cv2.imshow("Foreground Mask", foreground_mask) 
        

        
        key = cv2.waitKey(1) & 0xFF  
        if key == ord('q'):  
            break

    
    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()