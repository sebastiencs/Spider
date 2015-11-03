require 'test_helper'

class PaquetKeysControllerTest < ActionController::TestCase
  setup do
    @paquet_key = paquet_keys(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:paquet_keys)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create paquet_key" do
    assert_difference('PaquetKey.count') do
      post :create, paquet_key: { active: @paquet_key.active, date: @paquet_key.date, name: @paquet_key.name, pid: @paquet_key.pid, text: @paquet_key.text }
    end

    assert_redirected_to paquet_key_path(assigns(:paquet_key))
  end

  test "should show paquet_key" do
    get :show, id: @paquet_key
    assert_response :success
  end

  test "should get edit" do
    get :edit, id: @paquet_key
    assert_response :success
  end

  test "should update paquet_key" do
    patch :update, id: @paquet_key, paquet_key: { active: @paquet_key.active, date: @paquet_key.date, name: @paquet_key.name, pid: @paquet_key.pid, text: @paquet_key.text }
    assert_redirected_to paquet_key_path(assigns(:paquet_key))
  end

  test "should destroy paquet_key" do
    assert_difference('PaquetKey.count', -1) do
      delete :destroy, id: @paquet_key
    end

    assert_redirected_to paquet_keys_path
  end
end
