class PaquetMousesController < ApplicationController
  before_action :set_paquet_mouse, only: [:show, :edit, :update, :destroy]

  skip_before_action :verify_authenticity_token, only: [:new, :create]

  # GET /paquet_mouses
  # GET /paquet_mouses.json
  def index
    @paquet_mouses = PaquetMouse.all.paginate(:page => params[:page], :per_page => 50)
  end

  # GET /paquet_mouses/1
  # GET /paquet_mouses/1.json
  def show
  end

  # GET /paquet_mouses/new
  def new
    @paquet_mouse = PaquetMouse.new
  end

  # GET /paquet_mouses/1/edit
  def edit
  end

  # POST /paquet_mouses
  # POST /paquet_mouses.json
  def create
    @paquet_mouse = PaquetMouse.new(paquet_mouse_params)
    @paquet_mouse.save
    render nothing: true
  end

  # PATCH/PUT /paquet_mouses/1
  # PATCH/PUT /paquet_mouses/1.json
  def update
    respond_to do |format|
      if @paquet_mouse.update(paquet_mouse_params)
        format.html { redirect_to @paquet_mouse, notice: 'Paquet mouse was successfully updated.' }
        format.json { render :show, status: :ok, location: @paquet_mouse }
      else
        format.html { render :edit }
        format.json { render json: @paquet_mouse.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /paquet_mouses/1
  # DELETE /paquet_mouses/1.json
  def destroy
    @paquet_mouse.destroy
    respond_to do |format|
      format.html { redirect_to paquet_mouses_url, notice: 'Paquet mouse was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_paquet_mouse
      @paquet_mouse = PaquetMouse.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def paquet_mouse_params
      params.require(:paquet_mouse).permit(:name, :date, :active, :x, :y, :button, :pid)
    end
end
