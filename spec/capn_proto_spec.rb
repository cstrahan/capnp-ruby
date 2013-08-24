require 'capn_proto'

describe CapnProto do
  it "works" do
    CapnProto::SchemaParser
  end
end

describe CapnProto::ArrayPtr do
  it "works" do
    ptr = CapnProto::ArrayPtr.new(10, 3)
    expect(ptr.size).to eq 3
  end
end
