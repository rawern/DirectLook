#pragma once

#ifdef _WIN32
//#include <Windows.h>
#include <ppl.h>
#endif

#include <iostream>
#include <string>
#include <deque>

#include "GLMesh.h"
#include "TextureObject.h"
#include "../Image/GLSegmentedDepthImage.h"
#include "RenderTarget.h"
#include "SimpleTexture.h"
#include "AvVideoDecoder.h"

namespace DirectLook
{
	/// \brief Die Klasse GLScene repraesentiert einen 3D-Kopf der mithilfe der Tiefenwerte des Sensors erzeugt wird.
	class GLScene : public GLMesh 
	{

	private:
		TextureObject* m_pCameraTexture;		///< Kameratextur
		TextureObject* m_pDepthTexture;			///< Depth-Map Textur
		TextureObject* m_pBackgroundTexture;	///< Hintergrund Textur
		GLSegmentedDepthImage* m_pHeightMap;				///< Ist fuer die 3D-Rekonstruktion der Depth-Map Daten zustaendig
		
		unsigned int m_CameraWidth;				///< Breite der Kameratextur
		unsigned int m_CameraHeight;			///< Hoehe der Kameratextur
		unsigned int m_DepthWidth;				///< Breite der Depth-Map Textur
		unsigned int m_DepthHeight;				///< Hoehe der Depth-Map Textur
		
		RenderTarget* m_pRenderTarget;			///< Dient zum rendern der 3D-Szene in eine 2D-Textur
		SimpleTexture m_SimpleTexture;			///< Dient zum Anzeigen der gerenderten Szene
		bool m_TextureMode;						///< Kamera- oder Depth-Map Textur auf dem 3D-Model anzeigen?
		bool m_Background;						///< Hintergrundebene ein- oder ausblenden
		
		AvVideoDecoder m_pAvVidDecoder;
		string m_pVideoPath;
		bool m_pIsVideoPathSet;
		float m_pRatioW, m_pRatioH, m_pScaleX, m_pScaleY;
		GLuint m_pVidTexture[1];

	public:
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein GLScene-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param nearThreshold Near-Threshold fuer die Tiefensegmentierung des GLHeightMap-Objektes
		/// \param farThreshold  Far-Threshold  fuer die Tiefensegmentierung des GLHeightMap-Objektes
		/// \param cameraWidth	 Breite der Kameratextur
		/// \param cameraHeight	 Hoehe der Kameratextur
		/// \param depthWidth	 Breite der Depth-Map Textur
		/// \param depthHeight	 Hoehe der Depth-Map Textur
		/// \param pShader		 Shader-Objekt
		/// \param pCamera		 Virtuelle Kamera der 3D-Szene
		///
		////////////////////////////////////////////////////////////
		GLScene(
			const unsigned short nearThreshold,		// Near-Threshold fuer die Tiefensegmentierung des GLHeightMap-Objektes
			const unsigned short farThreshold,		// Far-Threshold  fuer die Tiefensegmentierung des GLHeightMap-Objektes
			const unsigned int cameraWidth,			// Breite der Kameratextur
			const unsigned int cameraHeight,		// Hoehe der Kameratextur
			const unsigned int depthWidth,			// Breite der Depth-Map Textur
			const unsigned int depthHeight,			// Hoehe der Depth-Map Textur
			Shader* pShader,						// Shader-Objekt
			GLCamera* pCamera						// Virtuelle Kamera
		);


		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Gibt den belegten Speicher vom GLScene-Objekt wieder frei.
		///
		////////////////////////////////////////////////////////////
		~GLScene(void);

		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Height-Map, die Kamera- und die Depth-Map Textur.
		///
		/// \param pImagePixels RGB-Werte des Sensors
		/// \param pDepthPixels Tiefenwerte des Sensors
		///
		////////////////////////////////////////////////////////////
		void updateData( const void* pImagePixels, const unsigned short* pDepthPixels );

		////////////////////////////////////////////////////////////
		/// \brief Wechselt zwischen der Kamera- und der Depth-Map Textur.
		////////////////////////////////////////////////////////////
		void switchTextureMode(void);

		////////////////////////////////////////////////////////////
		/// \brief Gibt den Winkel des Kinect-Motors, den Near- und den Far-Threshold in der Konsole aus.
		///
		/// \param motorAngle Winkel des Kinect-Motors in der Einheit Grad
		///
		////////////////////////////////////////////////////////////
		void showControlMenu( double motorAngle );

		////////////////////////////////////////////////////////////
		/// Setzt die virtuelle Kamera auf die Standardwerte zurueck.
		////////////////////////////////////////////////////////////
		void resetCamera(void);

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Werte des 3D-Kopfes auf die Standardwerte zurueck.
		////////////////////////////////////////////////////////////
		void resetModel(void);

		////////////////////////////////////////////////////////////
		/// \brief Laedt und kompiliert den Vertex- und Fragment-Shader-Code des 3D-Kopfes.
		////////////////////////////////////////////////////////////
		void reloadShaderProgram(void);

		////////////////////////////////
		// ueberladene GLMesh Methoden //
		////////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Erzeugt und initialisiert den 3D-Kopf.
		////////////////////////////////////////////////////////////
		void initialize(void);

		////////////////////////////////////////////////////////////
		/// \brief Zeichnet die 3D-Szene in eine RGB-Textur und zeigt diese an.
		////////////////////////////////////////////////////////////
		void draw(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Loescht die GLScene-Daten aus dem Videospeicher der Grafikkarte.
		/// Wird im Destruktor aufgerufen.
		///
		////////////////////////////////////////////////////////////
		void deleteResources(void);

		//////////////////////////////////////
		// GLScene Getter und Setter //
		//////////////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Breite der Kameratextur zurueck.
		///
		/// \return Breite der Kameratextur
		///
		////////////////////////////////////////////////////////////
		unsigned int getCameraWidth(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Hoehe der Kameratextur zurueck.
		///
		/// \return Hoehe der Kameratextur
		///
		////////////////////////////////////////////////////////////
		unsigned int getCameraHeight(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Breite der Depth-Map Textur zurueck.
		///
		/// \return Breite der Depth-Map Textur
		///
		////////////////////////////////////////////////////////////
		unsigned int getDepthWidth(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Hoehe der Depth-Map Textur zurueck.
		///
		/// \return Hoehe der Depth-Map Textur
		///
		////////////////////////////////////////////////////////////
		unsigned int getDepthHeight(void) const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert den aktuellen Near-Threshold der Tiefensegmentierung zurueck.
		///
		/// \return Near-Threshold der Tiefensegmentierung
		///
		////////////////////////////////////////////////////////////
		unsigned short getNearThreshold(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert den aktuellen Far-Threshold der Tiefensegmentierung zurueck.
		///
		/// \return Far-Threshold der Tiefensegmentierung
		///
		////////////////////////////////////////////////////////////
		unsigned short getFarThreshold(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Render-Target Textur im RGB-Format zurueck (performant).
		///
		/// \return Render-Target Textur im RGB-Format
		///
		////////////////////////////////////////////////////////////
		const GLubyte* getRGBPixels(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Render-Target Textur im RGB-Format zurueck (performant).
		///
		/// \param buffer  Zeiger auf den zu beschreibenden Puffer
		/// \param size    Groesse des zu beschreibenden Puffer
		/// \return        True wenn erfolgreich, false wenn fehlgeschlagen
		///
		////////////////////////////////////////////////////////////
		bool getRGBPixels(GLubyte* pBuffer, const unsigned int size) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Render-Target Textur im BGR-Format zurueck (performant).
		///
		/// \param buffer  Zeiger auf den zu beschreibenden Puffer
		/// \param size    Groesse des zu beschreibenden Puffer
		/// \return        True wenn erfolgreich, false wenn fehlgeschlagen
		///
		////////////////////////////////////////////////////////////
		bool getBGRPixels(GLubyte* pBuffer, const unsigned int size) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Render-Target Textur im YUV-Format zurueck (langsam).
		///
		/// \return Render-Target Textur im YUV-Format
		///
		////////////////////////////////////////////////////////////
		const GLubyte* getYUVPixels(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert true zurÃ¼ck wenn die Texure angezeigt wird und false wenn die Tiefenkarte angezeigt wird.
		///
		/// \return Texturmodus an oder aus
		///
		////////////////////////////////////////////////////////////
		bool getTextureMode(void) const { return m_TextureMode; }

		////////////////////////////////////////////////////////////
		/// \brief Blendet die Hintergrundebene ein oder aus.
		////////////////////////////////////////////////////////////
		void switchBackround(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert true zurÃ¼ck wenn der Hintergrund eingebelndet wird, ansonsten false.
		///
		/// \return Hintergrund ein- oder ausgebelndet
		///
		////////////////////////////////////////////////////////////
		bool getBackground(void) const { return m_Background; }

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Near-Threshold fuer die Tiefensegmentierung.
		///
		/// \param nearThreshold Near-Threshold fuer die Tiefensegmentierung
		///
		////////////////////////////////////////////////////////////
		void setNearThreshold( const unsigned short nearThreshold );

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Far-Threshold fuer die Tiefensegmentierung.
		///
		/// \param farThreshold Far-Threshold fuer die Tiefensegmentierung
		///
		////////////////////////////////////////////////////////////
		void setFarThreshold( const unsigned short farThreshold );

		void setBackgroundTexture( const unsigned int width, const unsigned int height, const GLubyte* pPixels );

		void setVideoPath(string path);
		
	private:
		////////////////////////////////////////////////////////////
		/// \brief Erzeugt und initialisiert den Element-Buffer.
		////////////////////////////////////////////////////////////
		void initElementBuffer(void);

		////////////////////////////////////////////////////////////
		/// \brief Erzeugt und initialsiert den Vertex-Buffer.
		////////////////////////////////////////////////////////////
		void initVertexBuffer(void);

		////////////////////////////////////////////////////////////
		/// \brief Erzeugt und initialisiert die Kamera- und Depth-Map Textur.
		////////////////////////////////////////////////////////////
		void initTextures(void);

		/*
		*	initializes the Background Video
		*/
		void initBackgroundVideo(void);

		/*
		*	draws the video onto a sky plane
		*/
		void drawBackgroundVideo(void);

		////////////////////////////////////////////////////////////
		/// \brief Zeichnet den 3D-Kopf.
		////////////////////////////////////////////////////////////
		void drawScene(void);

		////////////////////////////////////////////////////////////
		/// \brief Glättet die Tiefenkarte.
		////////////////////////////////////////////////////////////
		unsigned short* SmoothFilter(const unsigned short*);

		
	};
};
