class PaquetMouse
  include Mongoid::Document
  include Mongoid::Timestamps

  field :name, type: String
  field :date, type: String
  field :active, type: String
  field :x, type: Integer
  field :y, type: Integer
  field :button, type: String
  field :pid, type: Integer
end
