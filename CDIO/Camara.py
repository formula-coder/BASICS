import cv2
import numpy as np
import threading
from time import sleep

# Intentar importar SpeechRecognition/PyAudio
audio_available = True
try:
    import speech_recognition as sr
    reconocedor = sr.Recognizer()
    texto_detectado = "🎤 Escuchando..."
    detener = threading.Event()

    def escuchar_voz():
        global texto_detectado
        try:
            with sr.Microphone() as source:
                reconocedor.adjust_for_ambient_noise(source, duration=1)
                while not detener.is_set():
                    try:
                        audio = reconocedor.listen(source, timeout=1, phrase_time_limit=4)
                        texto = reconocedor.recognize_google(audio, language='es-ES')
                        texto_detectado = f"✓ {texto}"
                    except sr.WaitTimeoutError:
                        continue
                    except sr.UnknownValueError:
                        texto_detectado = "⚠ No entendí"
                    except sr.RequestError:
                        texto_detectado = "❌ Error"
                    except OSError:
                        texto_detectado = "❌ Sin micrófono"
                    sleep(0.05)
        except OSError:
            texto_detectado = "❌ Micrófono no detectado"

    hilo_voz = threading.Thread(target=escuchar_voz, daemon=True)
    hilo_voz.start()
except Exception:
    audio_available = False
    texto_detectado = "(Voz no disponible)"
    detener = threading.Event()

# Cargar cascadas de detección
face_cascade = cv2.CascadeClassifier(
    cv2.data.haarcascades + 'haarcascade_frontalface_default.xml'
)

# Configuración de la cámara
try:
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        raise SystemExit("No se pudo abrir la cámara")
except Exception:
    raise SystemExit("No se pudo abrir la cámara")

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        # Redimensionar a tamaño más pequeño y compacto
        frame = cv2.resize(frame, (800, 500))
        
        # Panel superior
        overlay = frame.copy()
        cv2.rectangle(overlay, (0, 0), (frame.shape[1], 70), (20, 20, 40), -1)
        cv2.addWeighted(overlay, 0.4, frame, 0.6, 0, frame)
        
        # Título
        cv2.putText(frame, "CAMARA + VOZ 🎬", (15, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.85, (0, 255, 150), 2)
        
        # Detectar rostros
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        rostros = face_cascade.detectMultiScale(gray, 1.3, 5, minSize=(30, 30))
        
        rostros_count = 0
        for (x, y, w, h) in rostros:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            cv2.circle(frame, (x + w//2, y + h//2), 5, (0, 255, 0), -1)
            cv2.putText(frame, "ROSTRO", (x, y-10),
                       cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
            rostros_count += 1
        
        # Detectar contornos/objetos
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)
        edges = cv2.Canny(blurred, 50, 150)
        contornos, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        objetos_count = 0
        for cnt in contornos[:10]:
            area = cv2.contourArea(cnt)
            if area > 300:
                x, y, w, h = cv2.boundingRect(cnt)
                cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
                objetos_count += 1
        
        # Información de detección
        info_text = f"Rostros: {rostros_count} | Objetos: {objetos_count}"
        cv2.putText(frame, info_text, (15, 55),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (200, 200, 100), 1)
        
        # Panel inferior con voz
        overlay = frame.copy()
        cv2.rectangle(overlay, (0, frame.shape[0]-50), (frame.shape[1], frame.shape[0]), (20, 20, 40), -1)
        cv2.addWeighted(overlay, 0.4, frame, 0.6, 0, frame)
        
        cv2.putText(frame, texto_detectado, (15, frame.shape[0]-20),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 100), 2)
        
        cv2.imshow('🎬 DETECCION INTELIGENTE', frame)
        
        # Solo Q para salir
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    detener.set()
    cap.release()
    cv2.destroyAllWindows()
    cv2.destroyAllWindows()
