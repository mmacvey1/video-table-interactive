//
//  Recipe.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/3/12.
//
//
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Font.h"
#include "Resources.h"
#include "RecipeView.h"
#include <stdio.h>
#include <stdlib.h>

RecipeView::RecipeView(RecipeModel _model){
  /*  recipeModel = _model;
    // menu_img.load(_model.getMenuImage());
    
    curStep = 0;
    stepState = 0;
    prevStepState = -1;
    prevStep = -1;
    
    
    console() << "this recipemodel has this many steps: " << recipeModel.getNumSteps() << "." << endl;
    for(int i=0;i<recipeModel.getNumSteps();i++){
        console() << "wtf: " << recipeModel.getCookStep(i).img << endl;
        gallerytools::Image anImage;
        anImage.load(recipeModel.getCookStep(i).img);
        anImage.hide();
        images.push_back(anImage);
        gallerytools::Video aVideo;
        aVideo.load(recipeModel.getCookStep(i).video);
        aVideo.hide();
        videos.push_back(aVideo);
    }
    
    string normalFont( "Arial" );
    
	TextLayout layout;
	layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
	layout.setFont( Font( normalFont, 24 ) );
	layout.setColor( Color( 1, 1, 1 ) );
	layout.addLine( "testing here");
	Surface8u rendered = layout.render( true, false );
	text_texture = gl::Texture( rendered );
*/
    console() << "error, this is deprecated" << endl;
    
}

RecipeView::RecipeView(UserAreaModel _area, RecipeModel _recipe){
    recipeModel = _recipe;
    areaModel = _area;
    // menu_img.load(_model.getMenuImage());
    
    curStep = 0;
    stepState = 0;
    prevStepState = -1;
    prevStep = -1;
    
    pos = Vec2f(_area.x,_area.y);
    rotation = _area.r;
    
    align=TOP_LEFT;
    
    if(_area.name.compare("bottom-left")==0) align=BOTTOM_LEFT;
    if(_area.name.compare("bottom-right")==0) align=BOTTOM_RIGHT;
    if(_area.name.compare("top-left")==0){
     align=BOTTOM_RIGHT;
        console() << "aligning top left";
    }
    if(_area.name.compare("top-right")==0){
        align=BOTTOM_LEFT;
    console() << "aligning top right";
    }
    console() << "this recipemodel has this many steps: " << recipeModel.getNumSteps() << "." << endl;
    for(int i=0;i<recipeModel.getNumSteps();i++){
        console() << "wtf: " << recipeModel.getCookStep(i).img << endl;
        gallerytools::Image anImage;
        anImage.load(recipeModel.getCookStep(i).img);
        anImage.hide();
        images.push_back(anImage);
        gallerytools::Video aVideo;
        aVideo.load(recipeModel.getCookStep(i).video);
        aVideo.hide();
        videos.push_back(aVideo);
    }
    
    string normalFont( "Arial" );
    
	TextLayout layout;
	layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
	layout.setFont( Font( normalFont, 24 ) );
	layout.setColor( Color( 1, 1, 1 ) );
	layout.addLine( "testing here");
	Surface8u rendered = layout.render( true, false );
	text_texture = gl::Texture( rendered );
    
    
}


void RecipeView::moveForward(){
    //stepState++;
    if(++stepState>1){
        stepState = 0;
        if(++curStep>=recipeModel.getNumSteps()){
            curStep = 0;
        }
    }
  //  img.load(recipeModel.getCookStep(curStep).img);
}

void RecipeView::update(){
    //img.update();
    // for(int i=0;i<videos.size();i++){
      //  if(i!=curStep){
       //     console() << "stopping video " << i << endl;
     //       videos.at(i).stop();
       // }
   // }
    for(int i=0;i<videos.size();i++){
        if(i!=curStep){
                      // videos.at(i).stop();
        }
    }
    if(stepState==1){
        if(videos.size()>curStep){
            videos.at(curStep).update();
            if(videos.at(curStep).isDone()) moveForward();
        }
    }
    
    char buffer [40];
  sprintf (buffer, "curStep: %i \n stepState: %i", curStep, stepState);
   // sprintf (buffer, "this: %s",recipeModel.name.c_str());
  
  //  buffer = *areaModel.name.c_str();
  //  console() << buffer << ", " << areaModel.name.c_str() <<  endl;
    TextLayout layout;
	layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
	layout.setFont( Font( "Arial", 18 ) );
	layout.setColor( Color( 1, 1, 1 ) );
    layout.addLine(recipeModel.name.c_str());
	layout.addLine( buffer);
	Surface8u rendered = layout.render( true, false );
    text_texture = gl::Texture( rendered );
    if(prevStep!=curStep){
        // moved from video to new start image
        // load both the image and the video for the new step

      //  videos.at(curStep).stop();
     //   videos.at(curStep).hide();
       if(prevStep>-1) videos.at(prevStep).stop();
        prevStep = curStep;
        
      //  videos.at(curStep).show();
     //   videos.at(curStep).play();
        
    }
    if(prevStepState!=stepState){
        // moved from start image to video
        //
        
        if(stepState==1){
           // video.fadeIn();
            
          if(videos.size()>curStep)    videos.at(curStep).show();
          if(images.size()>curStep)  images.at(curStep).hide();
            // img.fadeOut();
           if(videos.size()>curStep)   videos.at(curStep).play();
        } else {
            console() << "// does this ever even happen?" << endl;
            //img.fadeIn();
            //video.fadeOut();
           if(images.size()>curStep) images.at(curStep).show();
          if(videos.size()>curStep)  videos.at(curStep).hide();
          if(videos.size()>curStep)  videos.at(curStep).stop();
        }
     //   if(prevStepState==-1)  video.stop();
        prevStepState = stepState;
    }
    
}

void RecipeView::draw(){
    gl::pushMatrices();
   
    gl::enableAlphaBlending();
     
    (stepState == 0) ? gl::color(1.0f,1.0f,1.0f,0.5f) : gl::color(0.0f,1.0f,1.0f,0.5f);
    
   // Vec2f actualPos = Vec2f(getWindowWidth()*pos.x,getWindowHeight()*pos.y);
    gl::translate(pos);
    //gl::r
    gl::rotate(rotation);
    if(stepState==0){
        //for(int i=0;i<images.size();i++){
        //    if(i==curStep && stepState==0){
        //        gl::color(1.0f,0.0f,0.0f);
        //    } else {
                gl::color(1.0f,1.0f,1.0f);
        //    }
          if(images.size()>curStep) images.at(curStep).draw(align,true);
         //   gl::translate(25.0f,25.0f,0.0f);
     //   }
    } else {
        // for(int i=0;i<videos.size();i++){
        //    if(i==curStep && stepState!=0){
        //        gl::color(1.0f,0.0f,0.0f);
        //    } else {
                gl::color(1.0f,1.0f,1.0f);
        //    }
          if(videos.size()>curStep)  videos.at(curStep).draw(align,true);
        //      gl::translate(25.0f,25.0f,0.0f);
      //  }
      
    }
    // gl::translate(20,20,0);
   // menu_img.draw(CENTER,true);
    Rectf texRect = Rectf(0.0f,0.0f,text_texture.getWidth(),text_texture.getHeight());
    GalleryHelper::alignElement(align,Area(texRect));
    gl::draw(text_texture);
    gl::popMatrices();
}