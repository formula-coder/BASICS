import cv2
import speech_recognition as sr
import threading
from time import sleep

reconocedor = sr.Recognizer()
texto_detectado = "Esperando que hables..."
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
                    texto_detectado = f"Dices: {texto}"
                except sr.WaitTimeoutError:
                    continue
                except sr.UnknownValueError:
                    texto_detectado = "No entendí lo que dijiste"
                except sr.RequestError:
                    texto_detectado = "Error con el servicio de voz"
                except OSError:
                    texto_detectado = "No se pudo usar el micrófono"
                sleep(0.05)
    except OSError:
        texto_detectado = "No se detectó micrófono"

# Iniciar el hilo de voz en segundo plano
hilo_voz = threading.Thread(target=escuchar_voz, daemon=True)
hilo_voz.start()

# Configuración de la cámara
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    texto_detectado = "No se pudo abrir la camara"
    detener.set()
    raise SystemExit("No se pudo abrir la camara")

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            texto_detectado = "No se pudo leer la camara"
            break

        # Dibujar un fondo negro para el texto
        cv2.rectangle(frame, (0, frame.shape[0] - 50), (frame.shape[1], frame.shape[0]), (0, 0, 0), -1)

        # Poner el texto de la transcripción en la imagen
        cv2.putText(frame, texto_detectado, (20, frame.shape[0] - 20),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)

        cv2.imshow('Simulacion: Camara + Voz', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
finally:
    detener.set()
    cap.release()
    cv2.destroyAllWindows()
