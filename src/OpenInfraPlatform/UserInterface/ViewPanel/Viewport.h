/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef Blueform_UserInterface_Viewport_fbfab9db_0e02_4e25_a393_88c65a2ab542_h
#define Blueform_UserInterface_Viewport_fbfab9db_0e02_4e25_a393_88c65a2ab542_h

#include "OpenInfraPlatform/UserInterface/OpenInfraMap.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/eView.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
#include "OpenInfraPlatform/IfcGeometryConverter/ConverterBuw.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Tool.h"
#include "OpenInfraPlatform/DataManagement/Data.h"

//#include <BlueFramework/Engine/ViewCube/ViewCubeRefactored.h>
//#include <BlueFramework/Engine/ViewCube/Compass.h>
//#include <BlueFramework/Engine/ViewCube/RotationArrows.h>
//#include <BlueFramework/Engine/Camera/InfraCamera.h>
//#include <BlueFramework/Engine/Camera/InfraCameraController.h>
//#include <BlueFramework/Engine/Camera/SpectatorCamera.h>

#include <buw.h>
#include <QWidget>
#include <QMouseEvent>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class GradientClearEffect;
		class DEMEffect;
		class TrafficSignEffect;
		class AlignmentEffect;
		class GirderEffect;
		class SlabFieldEffect;
		class IfcGeometryEffect;
        class SkyboxEffect;
		class UIElements;

		class Viewport : public QWidget
		{
			Q_OBJECT;
			typedef DataManagement::ChangeFlag ChangeFlag;

		public:
			Viewport(const buw::eRenderAPI renderAPI, bool warp, bool msaa, QWidget* parent = nullptr);

			~Viewport();

			buw::Vector2i getSize() const;
			
			void goHome();

            void toggleSnow();

			void toggleCameraMode();
			void setCameraMode(buw::CameraController::eState mode);
			buw::CameraController::eState getCameraMode() const;

			void paintEvent(QPaintEvent * paintEvent);
			void resizeEvent(QResizeEvent *);
            
			void mousePressEvent(QMouseEvent *event) override;
			void mouseMoveEvent(QMouseEvent *event) override;
			void wheelEvent(QWheelEvent *event) override;
			void leaveEvent(QEvent *event) override;

			void keyPressEvent(QKeyEvent* event) override;
			void keyReleaseEvent(QKeyEvent* event) override;

			QPaintEngine* paintEngine() const {
				return nullptr;
			}

			void onChange();
			void onChange(ChangeFlag changeFlag);
			void onClear();

			void reloadShader();

			void setClearColor(const buw::Color3f& color);

			void setHideTerrain(const bool checked);
			void setDrawTerrainWireframe(const bool enable);
            void setDifferentColorsForAlignmentElements(const bool checked);
            void setHighlightSelectedAlignmentSegment(const bool checked);
			void enableTerrainTextured(const bool checked);
            void enableRoadBodyTextured(const bool checked);
			void enableIsoLines(const bool checked);
            void enableTerrainGradientRamp(const bool checked);

            void saveAsScreenshot(const std::string& filename);
            void storeGBuffer();

			void viewDirection(const buw::Vector3f& direction);

            void setView(eView type);
			void showCrossSection(const bool showCrossSection);
            void showDesignCrossSection(const bool showDesignCrossSections);
            void showRoadBodyWireframe(const bool connectCrossSections);
            void showRoadBodySolid(const bool checked);

            buw::ReferenceCounted<buw::ViewCube> getViewCube();
			buw::ReferenceCounted<AlignmentEffect> getAlignmentEffect();

		private:
			void updateWorldBuffer();
			void repositionCamera();

			void createDepthStencil();
			void resizeDepthStencil();

			void createIfcGeometry(buw::ReferenceCounted<IfcGeometryConverter::IfcGeometryModel> ifcGeometryModel);

		private Q_SLOTS:
			void tick();

		private:
			QTimer* timer_;

			buw::ReferenceCounted<buw::Camera> camera_;
			buw::ReferenceCounted<buw::CameraController> cameraController_;

            buw::ReferenceCounted<buw::ViewCube> viewCube_;

			buw::Vector2f lastMousePos_;
			buw::Vector3f minExtend_;
			buw::Vector3f maxExtend_;
			buw::Image4b depthBuffer_;

			std::chrono::nanoseconds lastTick_;

			buw::ReferenceCounted<buw::ITexture2D> terrainTexture_;

			buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
            buw::ReferenceCounted<buw::IViewport> viewport_;

			buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_;

            buw::ReferenceCounted<buw::ITexture2D> pickBuffer_;
            buw::ReferenceCounted<buw::ITexture2D> depthStencil_;


			buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_, viewportBuffer_, pickIdBuffer_;

			buw::ReferenceCounted<GradientClearEffect> gradientClearEffect_;
			buw::ReferenceCounted<DEMEffect> demEffect_;
			buw::ReferenceCounted<TrafficSignEffect> trafficSignEffect_;
			buw::ReferenceCounted<AlignmentEffect> alignmentEffect_;
			buw::ReferenceCounted<GirderEffect> girderEffect_;
			buw::ReferenceCounted<SlabFieldEffect> slabFieldEffect_;
            buw::ReferenceCounted<IfcGeometryEffect> ifcGeometryEffect_;
			buw::ReferenceCounted<UIElements> uiElements_;
            buw::ReferenceCounted<SkyboxEffect> skyboxEffect_;
            std::vector<buw::ReferenceCounted<buw::Effect>> activeEffects_;

			// Clear
			bool gradientClear_ = true;
            bool snow_ = false;
			buw::Color3f clearColor_;

			int									selectedAlignmentIndex_;
            UINT currentPickId_ = -1;
			buw::Image4b pickIdImage_;

		};

		//class Viewport : public QWidget
		//{
		//	Q_OBJECT;

		//	typedef DataManagement::ChangeFlag ChangeFlag;

		//public:			
		//	//---------------------------------------------------------------------------//
		//	// Events
		//	//---------------------------------------------------------------------------//

		//	boost::signals2::signal<void(buw::eViewCubeOrientation::Enum)> ViewCubeSelectionChanged;
  //          boost::signals2::signal<void(buw::Vector2f)> Rotate;

		//public:
		//	Viewport(const buw::renderWindowsDescription& rwd, QWidget* parent);

		//	virtual ~Viewport();

		//	//! Draws the scene.
		//	void	paintEvent(QPaintEvent *);

		//	QPaintEngine* paintEngine() const;

		//	void	resizeEvent(QResizeEvent *);

		//	void	onChange();
		//	void	onChange(ChangeFlag changeFlag);
		//	void	onClear();

		//	void	forceRepaint();
		//	void    startContinuousRendering();
		//	void	stopContinuousRendering();
		//	
		//	eView	getView() const;
		//	void	setView(eView val);

		//	void	showCrossSection(const bool showCrossSection);
		//	void	showDesignCrossSection( const bool showDesignCrossSection );
		//	void	connectCrossSections(const bool connectCrossSections);
		//	void	doSolidCrossSections(const bool solidCrossSections);
		//	void	drawRoadTexture(const bool drawRoadTexture);

		//	void	enableCreatePoints( bool checked );

		//	std::vector<buw::Vector3d> getAlignmentPoints();

		//	buw::Vector3d	getOffset() const;

		//	void reloadShader();

		//	void storeGBuffer();

		//	// Quick hack for imporing bridge models
		//	bool bBridgeLoaded = false;
		//	void LoadBridge();

		//	void RenderBridge();

		//	//---------------------------------------------------------------------------//
		//	// Alignment
		//	//---------------------------------------------------------------------------//

		//	void	setHighlightDifferentAlignmentElements( const bool enable );
		//	void	setHighlightSelectedAlignmentSegment( const bool enable );
		//	
		//	//---------------------------------------------------------------------------//
		//	// Terrain
		//	//---------------------------------------------------------------------------//

		//	void	setHideTerrain(const bool checked );
		//	bool	getDrawTerrainWireframe() const;
		//	void	setDrawTerrainWireframe(const bool enable);
		//	void	enableTerrainTextured(const bool checked );
		//	void	enableTerrainGradientRamp(const bool enable);
		//	void	enableIsoLines(const bool enable);

		//	//---------------------------------------------------------------------------//
		//	// LaserScan
		//	//---------------------------------------------------------------------------//
		//	
		//	void	setUseUniformPointColor(const bool useUniformColor);
		//	void	setUseUniformPointSize(const bool useUniformSize);
		//	void	setPointSize(const float size);

		//	//---------------------------------------------------------------------------//
		//	// BlueMaps
		//	//---------------------------------------------------------------------------//

		//	QWidget* enableBlueMap(const bool checked);

		//	//---------------------------------------------------------------------------//
		//	// Clear
		//	//---------------------------------------------------------------------------//

		//	void	setClearColor(const buw::Color3f& color);	

		//	//---------------------------------------------------------------------------//
		//	// Common
		//	//---------------------------------------------------------------------------//

		//	buw::Vector2i getSize() const;

		//	void setProjectionType(const buw::eProjectionType::Enum type);

		//	void saveAsScreenshot( const std::string& filename );

		//	void showFrameTimes(const bool show);

  //          //---------------------------------------------------------------------------//
  //          // ViewCube, Compass, RotationArrows and PickIdGenerator
  //          //---------------------------------------------------------------------------//
  //          int updateViewCube(const std::string &filename);

  //          void updateCompass();

  //          void updateRotationArrows();

  //          void setUseLegacy(bool value);

  //          void setShowViewCube(bool value);

  //          void setShowCompass(bool value);

  //          void setShowRotationArrows(bool value);

		//	//---------------------------------------------------------------------------//
		//	// Control
		//	//---------------------------------------------------------------------------//
		//	void				viewDirection(const buw::Vector3f& direction);
		//	void				repositionCameraTarget();

		//	void setInfraCameraController(buw::ReferenceCounted<buw::InfraCameraController> controller);
		//	buw::ReferenceCounted<buw::InfraCameraController> getInfraCameraController();

		//public Q_SLOTS:

		//	void drawNextFrame();

		//protected:
		//	void leaveEvent ( QEvent * );

		//	//! Receive mouse press events for the widget.
		//	void mousePressEvent(QMouseEvent *event);

		//	//! Receives wheel events for the widget.
		//	void wheelEvent(QWheelEvent  * event);
		//	
		//	void mouseMoveEvent(QMouseEvent *event);

		//	//! Called whenever a key is pressed.
		//	void keyPressEvent(QKeyEvent *event);

		//	//! Called whenever a key is released.
		//	void keyReleaseEvent(QKeyEvent *event);

		//	//! Receives mouse release events for the widget.
		//	/*
		//		\param[in] event	Contains parameters that describe a mouse event.
		//	*/
		//	void mouseReleaseEvent(QMouseEvent *event);

		//private:		
		//	void			updateFrustumProjection();
		//	void			createGraphicResources();
		//	void			createSkyboxResources();
		//	void			createDigitalElevationModel();

		//	void			createAlignment();
		//	void			createAlignmentHorizontal(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel);
		//	void			createAlignmentVertical(buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> alignmentModel);
		//	void			createAlignmentThreeDimensional();
		//	void			createIfcGeometry(buw::ReferenceCounted<IfcGeometryConverter::IfcGeometryModel> ifcGeometryModel);
		//	void			createBoundingBoxes(buw::Vector3d min, buw::Vector3d max);

		//	void			createAlignmentThreeDimensional_CrossSection();

		//	void			generatePickRay(int sx, int sy, buw::Vector3f& o_start, buw::Vector3f& o_end);

		//	float			getAspectRatio() const;

		//	void			createRenderSystem(const buw::renderWindowsDescription& rwd);

		//	void			fillVertexCacheUIElements();

		//	void			drawTerrain();

		//	buw::Vector3f	unproject(const buw::Vector3f &point);
		//	buw::Vector3f	screenToWorld(const float x, const float y, const float z/*=0.0f*/);
		//	void			pick(int sx, int sy, buw::Vector3f& o_start, buw::Vector3f& o_end);

		//	void			drawFullScreenQuad();

		//	void			createPickBufferRenderTarget();
		//	void			createDeferredRenderTargets();

		//	void			fillGBuffer();

		//	void			createCpuReadTexture();;
  //          void            createCpuReadTextureBuffer();

  //          void            createCpuReadPickBuffer();

		//	//buw::Vector4f	getPickBufferColor(const int x, const int y);
  //          buw::uint32     getPickBufferColor(const int x, const int y);
  //          buw::Vector4f   getLegacyPickBufferColor(const int x, const int y);
		//	buw::Vector4f	getGBufferColor(const int x, const int y);

		//	void			storePickBuffer();

		//	void			onViewCubeSelectionChanged(buw::eViewCubeOrientation::Enum state);

  //          void            onRotationArrowsClicked(buw::Vector2f value);

		//	// road body
		//	buw::matrix44d getGlobalRotationMatrixOnStation(
		//		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment, 
		//		buw::Stationing station);

		//	void drawCrossSection(
		//		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment,
		//		buw::ReferenceCounted<buw::CrossSectionStatic> cs, 
		//		buw::Vector3d offsetViewArea);

		//	void drawRoadBodyBetweenStation(
		//		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment, 
		//		buw::ReferenceCounted<buw::CrossSectionStatic> cs, 
		//		buw::ReferenceCounted<buw::CrossSectionStatic> nextCs, 
		//		buw::Vector3d offsetViewArea);

		//private:
		//	buw::ReferenceCounted<buw::SkinnedMesh>				mesh_;

		//	buw::ReferenceCounted<ToolManager>					toolManager_;

		//	int									selectedAlignmentIndex_;
		//	int									hoveredAlignmentIndex_;

		//	// ViewCube
		//	buw::ReferenceCounted<buw::ViewCube>					viewCubeLegacy_;
  //          buw::ReferenceCounted<buw::ViewCube2>			        viewCube_;
  //          buw::ReferenceCounted<buw::Compass>				        compass_;
  //          buw::ReferenceCounted<buw::RotationArrows>              rotationArrows_;

  //          buw::ReferenceCounted<buw::PickIdGenerator>		        generator_;

		//	buw::ReferenceCounted<buw::IDepthStencilState>		    ddsDisableDepthTest_;
		//	buw::ReferenceCounted<buw::IRasterizerState>            rsDefault_;
		//	buw::ReferenceCounted<buw::IRasterizerState>			rsCullBackFaces_;

		//	bool								                    bShowViewCube_;
		//	bool								                    bContinuousRendering_;            
  //          bool                                                    bShowLegacy_;
  //          bool                                                    bShowCompass_;
  //          bool                                                    bShowRotationArrows_;


		//	buw::ReferenceCounted<buw::ITexture2D>				cpuReadTexture_;

		//	// PickBuffer			
		//	buw::Vector4f						clearPickColor;
		//	buw::ReferenceCounted<buw::IRenderTargetTexture2D>	renderTargetPickBuffer_;

  //          buw::uint32										pickColor_;	// is updated by each mouse move event
  //          buw::Vector4f                                   pickColorLegacy_;
  //         
  //          buw::ReferenceCounted<buw::ITexture2D>				cpuReadTextureBuffer_;
  //          buw::ReferenceCounted<buw::ITexture2D>				cpuReadPickBuffer_;


		//	// GBuffer
		//	buw::ReferenceCounted<buw::IShader>					gBufferShader_;
		//	buw::ReferenceCounted<buw::IRenderTargetTexture2D>	renderTargetGBuffer_;

		//	// LaserScan
		//	bool								bUseUniformPointColor_;
		//	bool								bUseUniformPointSize_;
		//	float								pointSize_;

		//	// BlueMap
		//	buw::ReferenceCounted<buw::OpenInfraMap>	blueMap_;
		//	
		//	buw::ReferenceCounted<Hud>							hud_;
		//	static const bool					bShowHud = false;

		//	// Clear
		//	bool								gradientClear_;
		//	buw::ReferenceCounted<buw::IDepthStencilState>		dssDefault_;
		//	buw::ReferenceCounted<buw::IDepthStencilState>		ddsDisableDepthWrite_;
		//	buw::ReferenceCounted<buw::IShader>					shaderGradientQuad_;
		//	buw::Color3f						clearColor_;

		//	bool								bHighlightDifferentAlignmentElements_;
		//	bool								bHighlightSelectedAlignmentSegment_;

		//	// alignment editor
		//	bool								bCreatePoints_;
		//	buw::ReferenceCounted<buw::RoadDesignVCL>				vertexCacheAlignmentEditorLine_;
		//	buw::ReferenceCounted<buw::RoadDesignVCP>				vertexCacheAlignmentEditorPoint_;
		//	std::vector<buw::Vector3d>			alignmentEditorPoints_;

		//	buw::ReferenceCounted<buw::VertexCachePointT<buw::VertexPosition3Color3>>	vertexCachePointLaserScan_;
		//	buw::ReferenceCounted<buw::IShader>					shaderLaserScan_;

		//	eView								view_;
		//	buw::eProjectionType::Enum			projectionType_;
		//	
		//	buw::ReferenceCounted<buw::IRenderSystem>				renderSystem_;
		//	buw::ReferenceCounted<buw::IRenderContext>			renderContext_;

		//	buw::ReferenceCounted<buw::VertexCacheTriangle>		vertexCacheAlignmentTriangle_;
		//	buw::ReferenceCounted<buw::IShader>					triangleShader_;
		//	buw::ReferenceCounted<buw::RoadDesignVCL>				vertexCacheAlignmentLine_;
		//	buw::ReferenceCounted<buw::RoadDesignVCP>				vertexCacheAlignmentPoint_;

		//	buw::ReferenceCounted<buw::VertexCacheTriangleT<VertexLayout>> vertexCacheIfcGeometry_;
		//	buw::ReferenceCounted<buw::RoadDesignVCL>				vertexCacheIfcPolylines_;

		//	buw::ReferenceCounted<buw::VertexCacheLine>			vertexCacheLineUIElements;
		//	buw::ReferenceCounted<buw::VertexCachePoint>			vertexCachePointDebug_;
		//	buw::ReferenceCounted<buw::VertexCacheLine>			vertexCacheLineDebug_;
		//	
		//	std::vector<buw::ReferenceCounted<buw::VertexCacheLine>>	vertexCacheLineBreakLines_;

		//	buw::ReferenceCounted<buw::IRasterizerState>			rsSolidFill_;
		//	buw::ReferenceCounted<buw::IRasterizerState>			rsWireframeFill_;
		//	buw::ReferenceCounted<buw::ISamplerState>				sampler_;

		//	// DigitalElevationModel
		//	bool								bTerrainTextured_;
		//	bool								bTerrainUseColorRamp_;
		//	bool								bTerrainDisplayIsoLines_;
		//	buw::ReferenceCounted<buw::ITexture2D>				terrainTexture_;
		//	buw::ReferenceCounted<buw::ITexture1D>				gradientRampTexture_;
		//	bool								bHideTerrain_;
		//	bool								bDrawTerrainWireframe_;
		//	buw::Vector2f						heightRange_;

		//	buw::ReferenceCounted<buw::ISamplerState>				colorRampSampler_;
		//	
		//	std::vector<buw::ReferenceCounted<buw::IndexedMesh>>	meshesDigitalElevationModel_;
		//	buw::ReferenceCounted<buw::IShader>					shaderDigitalElevationModel_;
		//	buw::ReferenceCounted<buw::IShader>					shaderDigitalElevationModelColorRamp_;
		//	buw::ReferenceCounted<buw::IVertexLayout>				vertexLayoutDigitalElevationModel_;

		//	//  Text
		//	buw::ReferenceCounted<buw::SignedDistanceFont>		signedDistanceFont_;
		//	buw::ReferenceCounted<buw::Text>						text_;

		//	//---------------------------------------------------------------------------//
		//	// Camera control
		//	//---------------------------------------------------------------------------//
		//	buw::ReferenceCounted<buw::InfraCamera>				infraCamera_;
		//	buw::ReferenceCounted<buw::InfraCameraController>		infraCameraController_;
		//	unsigned long						lastTick_;
		//	buw::Vector2f						lastMousePos_;

		//	// Skybox
		//	bool								drawSkybox_;
		//	buw::ReferenceCounted<buw::Skybox>					skybox_;

		//	//---------------------------------------------------------------------------//
		//	// CrossSections
		//	//---------------------------------------------------------------------------//
		//	bool								showCrossSection_;
		//	bool								showDesignCrossSection_;
		//	bool								connectCrossSections_;
		//	bool								doSolidCrossSections_;
		//	bool								drawRoadTexture_;

		//	buw::ReferenceCounted<buw::ITexture2D>															roadTexture_;
		//	buw::ReferenceCounted<buw::VertexCacheTriangleT<buw::VertexPosition3Color3Normal3Texture2>>		triangleCacheP3C3N3UV2_;
		//	buw::ReferenceCounted<buw::IShader>																triangleShaderP3C3N3UV2_;

		//	//---------------------------------------------------------------------------//
		//	// Diagnostics
		//	//---------------------------------------------------------------------------//
		//	buw::Timer	performanceTimer_;
		//	double		lastPreFrame_;
		//	long long	frameTime_;
		//	long long	sinceLastFrame_;
		//	bool		bShowFrameTimes_;
		//}; // end class Viewport
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

//namespace buw
//{
//	using OpenInfraPlatform::UserInterface::eView;
//	using OpenInfraPlatform::UserInterface::Viewport;
//}

#endif // end define Blueform_UserInterface_Viewport_fbfab9db_0e02_4e25_a393_88c65a2ab542_h