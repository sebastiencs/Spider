json.array!(@paquet_keys) do |paquet_key|
  json.extract! paquet_key, :id, :name, :date, :active, :text, :pid
  json.url paquet_key_url(paquet_key, format: :json)
end
