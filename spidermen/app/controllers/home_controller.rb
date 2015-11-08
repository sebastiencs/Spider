class HomeController < ApplicationController

  def index
    @paquet_keys = PaquetKey.all
    @paquet_mouses = PaquetMouse.all
    @paquet_mouses_none = PaquetMouse.where(button: "None")
    @paquet_mouses_left = PaquetMouse.where(button: "Left")
    @paquet_mouses_right = PaquetMouse.where(button: "Right")
    @paquet_mouses_middle = PaquetMouse.where(button: "Middle")
    @paquet_mouses_x1 = PaquetMouse.where(button: "X1Button")
    @paquet_mouses_x2 = PaquetMouse.where(button: "X2Button")
  end
  
  def team
  end
  
end
