import cv2
import numpy as np
import threading
from time import sleep


def clamp(value, minimum, maximum):
    return max(minimum, min(maximum, value))


def draw_rounded_panel(frame, top_left, bottom_right, color, alpha=0.78, radius=14):
    overlay = frame.copy()
    x1, y1 = top_left
    x2, y2 = bottom_right
    cv2.rectangle(overlay, (x1 + radius, y1), (x2 - radius, y2), color, -1)
    cv2.rectangle(overlay, (x1, y1 + radius), (x2, y2 - radius), color, -1)
    cv2.circle(overlay, (x1 + radius, y1 + radius), radius, color, -1)
    cv2.circle(overlay, (x2 - radius, y1 + radius), radius, color, -1)
    cv2.circle(overlay, (x1 + radius, y2 - radius), radius, color, -1)
    cv2.circle(overlay, (x2 - radius, y2 - radius), radius, color, -1)
    cv2.addWeighted(overlay, alpha, frame, 1 - alpha, 0, frame)


def draw_label(frame, text, origin, color, scale=0.58, thickness=1, text_color=(255, 255, 255)):
    x, y = origin
    (width, height), baseline = cv2.getTextSize(text, cv2.FONT_HERSHEY_SIMPLEX, scale, thickness)
    padding_x = 12
    padding_y = 8
    draw_rounded_panel(
        frame,
        (x, y - height - padding_y),
        (x + width + padding_x * 2, y + baseline + padding_y),
        color,
        alpha=0.9,
        radius=12,
    )
    cv2.putText(
        frame,
        text,
        (x + padding_x, y),
        cv2.FONT_HERSHEY_SIMPLEX,
        scale,
        text_color,
        thickness,
        cv2.LINE_AA,
    )


def draw_counter_card(frame, top_left, title, value, accent_color, width=180, height=72):
    x, y = top_left
    draw_rounded_panel(frame, (x, y), (x + width, y + height), (22, 24, 36), alpha=0.86, radius=16)
    cv2.rectangle(frame, (x, y), (x + 8, y + height), accent_color, -1)
    cv2.putText(frame, title, (x + 20, y + 26), cv2.FONT_HERSHEY_SIMPLEX, 0.48, (190, 196, 210), 1, cv2.LINE_AA)
    cv2.putText(frame, str(value), (x + 20, y + 57), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (255, 255, 255), 2, cv2.LINE_AA)


def draw_simple_hud(frame, voice_text, faces_count, objects_count):
    height, width = frame.shape[:2]

    # Header
    draw_rounded_panel(frame, (12, 12), (width - 12, 84), (15, 18, 34), alpha=0.88, radius=20)
    cv2.circle(frame, (38, 48), 14, (0, 220, 180), -1)
    cv2.circle(frame, (38, 48), 6, (255, 255, 255), -1)
    cv2.putText(frame, "CAMARA + VOZ", (64, 44), cv2.FONT_HERSHEY_SIMPLEX, 0.82, (255, 255, 255), 2, cv2.LINE_AA)
    cv2.putText(frame, "Vista en primera persona", (64, 68), cv2.FONT_HERSHEY_SIMPLEX, 0.52, (170, 178, 195), 1, cv2.LINE_AA)
    draw_label(frame, "Q para salir", (width - 128, 57), (70, 78, 110), scale=0.5, thickness=1)

    # Counters
    draw_counter_card(frame, (16, 98), "Rostros", faces_count, (0, 180, 120), width=180)
    draw_counter_card(frame, (206, 98), "Objetos", objects_count, (70, 120, 255), width=180)

    # Voice/status panel
    panel_x1 = 16
    panel_y1 = height - 96
    panel_x2 = width - 16
    panel_y2 = height - 16
    draw_rounded_panel(frame, (panel_x1, panel_y1), (panel_x2, panel_y2), (15, 18, 34), alpha=0.88, radius=20)
    cv2.putText(frame, "Estado de voz", (panel_x1 + 18, panel_y1 + 30), cv2.FONT_HERSHEY_SIMPLEX, 0.56, (175, 182, 200), 1, cv2.LINE_AA)

    status_color = (0, 220, 120)
    if voice_text.startswith("ERROR"):
        status_color = (60, 100, 255)
    elif voice_text.startswith("NO ENTENDI"):
        status_color = (0, 200, 255)
    elif voice_text.startswith("("):
        status_color = (160, 160, 160)

    draw_label(frame, voice_text, (panel_x1 + 16, panel_y1 + 65), status_color, scale=0.56, thickness=1)


def stylize_face(frame, x, y, w, h):
    corner = clamp(min(w, h) // 6, 10, 26)
    color = (0, 255, 170)
    thickness = 2

    cv2.line(frame, (x, y), (x + corner, y), color, thickness)
    cv2.line(frame, (x, y), (x, y + corner), color, thickness)
    cv2.line(frame, (x + w - corner, y), (x + w, y), color, thickness)
    cv2.line(frame, (x + w, y), (x + w, y + corner), color, thickness)
    cv2.line(frame, (x, y + h - corner), (x, y + h), color, thickness)
    cv2.line(frame, (x, y + h), (x + corner, y + h), color, thickness)
    cv2.line(frame, (x + w - corner, y + h), (x + w, y + h), color, thickness)
    cv2.line(frame, (x + w, y + h - corner), (x + w, y + h), color, thickness)

    cv2.circle(frame, (x + w // 2, y + h // 2), 5, color, -1)

# Intentar importar SpeechRecognition/PyAudio
audio_available = True
try:
    import speech_recognition as sr
    reconocedor = sr.Recognizer()
    texto_detectado = "ESCUCHANDO..."
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
                        texto_detectado = f"OK {texto}"
                    except sr.WaitTimeoutError:
                        continue
                    except sr.UnknownValueError:
                        texto_detectado = "NO ENTENDI"
                    except sr.RequestError:
                        texto_detectado = "ERROR"
                    except OSError:
                        texto_detectado = "SIN MICROFONO"
                    sleep(0.05)
        except Exception:
            texto_detectado = "MICROFONO NO DETECTADO"
            return

    hilo_voz = threading.Thread(target=escuchar_voz, daemon=True)
    hilo_voz.start()
except Exception:
    audio_available = False
    texto_detectado = "(VOZ NO DISPONIBLE)"
    detener = threading.Event()

# Cargar cascadas de detección
face_cascade = cv2.CascadeClassifier(
    cv2.data.haarcascades + 'haarcascade_frontalface_default.xml'
)

# Configuración de la cámara
cap = None
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
        
        # Redimensionar a un lienzo consistente para el HUD
        frame = cv2.resize(frame, (800, 500))

        # Capa base de contraste para que la interfaz se vea más limpia
        base = frame.copy()
        cv2.rectangle(base, (0, 0), (frame.shape[1], frame.shape[0]), (10, 12, 18), -1)
        cv2.addWeighted(base, 0.10, frame, 0.90, 0, frame)
        
        # Detectar rostros
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        rostros = face_cascade.detectMultiScale(gray, 1.3, 5, minSize=(30, 30))
        
        rostros_count = 0
        for (x, y, w, h) in rostros:
            stylize_face(frame, x, y, w, h)
            draw_label(frame, "ROSTRO", (x, y - 8), (0, 170, 120), scale=0.48, thickness=1)
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
                cv2.rectangle(frame, (x, y), (x + w, y + h), (70, 120, 255), 2)
                cv2.circle(frame, (x + w // 2, y + h // 2), 4, (70, 120, 255), -1)
                objetos_count += 1

        draw_simple_hud(frame, texto_detectado, rostros_count, objetos_count)
        
        cv2.imshow('DETECCION INTELIGENTE', frame)
        
        # Solo Q para salir
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    detener.set()
    if cap is not None:
        cap.release()
    cv2.destroyAllWindows()
