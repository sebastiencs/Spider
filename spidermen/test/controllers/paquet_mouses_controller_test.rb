require 'test_helper'

class PaquetMousesControllerTest < ActionController::TestCase
  setup do
    @paquet_mouse = paquet_mouses(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:paquet_mouses)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create paquet_mouse" do
    assert_difference('PaquetMouse.count') do
      post :create, paquet_mouse: { active: @paquet_mouse.active, date: @paquet_mouse.date, name: @paquet_mouse.name, pid: @paquet_mouse.pid, x: @paquet_mouse.x, y: @paquet_mouse.y }
    end

    assert_redirected_to paquet_mouse_path(assigns(:paquet_mouse))
  end

  test "should show paquet_mouse" do
    get :show, id: @paquet_mouse
    assert_response :success
  end

  test "should get edit" do
    get :edit, id: @paquet_mouse
    assert_response :success
  end

  test "should update paquet_mouse" do
    patch :update, id: @paquet_mouse, paquet_mouse: { active: @paquet_mouse.active, date: @paquet_mouse.date, name: @paquet_mouse.name, pid: @paquet_mouse.pid, x: @paquet_mouse.x, y: @paquet_mouse.y }
    assert_redirected_to paquet_mouse_path(assigns(:paquet_mouse))
  end

  test "should destroy paquet_mouse" do
    assert_difference('PaquetMouse.count', -1) do
      delete :destroy, id: @paquet_mouse
    end

    assert_redirected_to paquet_mouses_path
  end
end
