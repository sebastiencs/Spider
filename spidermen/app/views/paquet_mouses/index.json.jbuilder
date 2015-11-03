json.array!(@paquet_mouses) do |paquet_mouse|
  json.extract! paquet_mouse, :id, :name, :date, :active, :x, :y, :pid
  json.url paquet_mouse_url(paquet_mouse, format: :json)
end
