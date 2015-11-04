class PaquetKeysController < ApplicationController
  before_action :set_paquet_key, only: [:show, :edit, :update, :destroy]
  
  skip_before_action :verify_authenticity_token, only: [:new, :create]

  # GET /paquet_keys
  # GET /paquet_keys.json
  def index
    @paquet_keys = PaquetKey.all.paginate(:page => params[:page], :per_page => 50)
  end

  # GET /paquet_keys/1
  # GET /paquet_keys/1.json
  def show
  end

  # GET /paquet_keys/new
  def new
    @paquet_key = PaquetKey.new
  end

  # GET /paquet_keys/1/edit
  def edit
  end

  # POST /paquet_keys
  # POST /paquet_keys.json
  def create
    @paquet_key = PaquetKey.new(paquet_key_params)
    @paquet_key.save
    render nothing: true
  end

  # PATCH/PUT /paquet_keys/1
  # PATCH/PUT /paquet_keys/1.json
  def update
    respond_to do |format|
      if @paquet_key.update(paquet_key_params)
        format.html { redirect_to @paquet_key, notice: 'Paquet key was successfully updated.' }
        format.json { render :show, status: :ok, location: @paquet_key }
      else
        format.html { render :edit }
        format.json { render json: @paquet_key.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /paquet_keys/1
  # DELETE /paquet_keys/1.json
  def destroy
    @paquet_key.destroy
    respond_to do |format|
      format.html { redirect_to paquet_keys_url, notice: 'Paquet key was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_paquet_key
      @paquet_key = PaquetKey.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def paquet_key_params
      params.require(:paquet_key).permit(:name, :date, :active, :text, :pid)
    end
end
